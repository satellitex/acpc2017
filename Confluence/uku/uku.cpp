#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <utility>

using namespace std;

#define MAX_N 100000

using ll = long long;

const int inf = 1<<25;

struct edge {
  int to, cost;
  edge(int to, int cost):to(to), cost(cost){}
};

using Graph = vector<vector<edge>>;
using Pi = pair<int, int>;

int N, M, T, Q;
Graph graph, dag;

// build shortest path tree by Dijkstra
vector<int> dist;
vector<vector<Pi>> par;
void buildShortestPathDAG() {
  dist.resize(N, inf);
  par.resize(N);
  dist[T] = 0;
  priority_queue<Pi, vector<Pi>, greater<Pi> > que;
  que.emplace(0, T);
  while(!que.empty()) {
    Pi p = que.top(); que.pop();
    int v = p.second;
    if(dist[v] < p.first) continue;
    for(int i = 0; i < (int)graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(e.cost+dist[v] < dist[e.to]) {
	dist[e.to] = e.cost+dist[v];
	par[e.to].clear();
	par[e.to].emplace_back(v, i);
	que.emplace(dist[e.to], e.to);
      } else if(e.cost+dist[v] == dist[e.to]) {
	par[e.to].emplace_back(v, i);
      }
    }
  }

  dag.resize(N);
  for(int v = 0; v < N; v++) {
    for(Pi& p : par[v]) {
      int cost = graph[p.first][p.second].cost;
      dag[v].emplace_back(p.first, cost);
    }
  }
}

vector<int> dijkstra(int s) {
  vector<int> res(N, inf);
  res[s] = 0;
  priority_queue<Pi, vector<Pi>, greater<Pi> > que;
  que.emplace(0, s);
  while(!que.empty()) {
    Pi p = que.top(); que.pop();
    int v = p.second;
    if(res[v] < p.first) continue;
    for(edge& e : dag[v]) {
      if(e.cost+res[v] < res[e.to]) {
	res[e.to] = e.cost+res[v];
	que.emplace(res[e.to], e.to);
      }
    }
  }
  return res;
}

int getLCA(int u, int v) {
  vector<int> d1 = dijkstra(u);
  vector<int> d2 = dijkstra(v);
  int lca = 0;
  for(int i = 0; i < N; i++) {
    if(d1[i]+d2[i] < d1[lca]+d2[lca]) lca = i;
  }
  return lca;
}

int main() {
  cin >> N >> M >> T;
  --T;
  graph.resize(N);
  for(int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    graph[a].emplace_back(b, c);
    graph[b].emplace_back(a, c);
  }
  buildShortestPathDAG();
  cin >> Q;
  for(int i = 0; i < Q; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    int lca = getLCA(u, v);
    //cout << dist[u] << " " << dist[v] << " " << lca << " " << dist[lca] << endl;
    cout << max(dist[u], dist[v]) - dist[lca] << endl;
  }

  return 0;
}
