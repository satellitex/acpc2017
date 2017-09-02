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
Graph graph, tree;

// build shortest path tree by Dijkstra
vector<int> dist, prevv, preve;
void buildShortestPathTree() {
  dist.resize(N, inf);
  prevv.resize(N, -1);
  preve.resize(N, -1);
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
	prevv[e.to] = v; preve[e.to] = i;
	que.emplace(dist[e.to], e.to);
      } else if(e.cost+dist[v] == dist[e.to]) {
	if(e.cost < graph[prevv[e.to]][preve[e.to]].cost) {
	  prevv[e.to] = v; preve[e.to] = i;
	}
      }
    }
  }

  tree.resize(N);
  for(int v = 0; v < N; v++) {
    if(v == T) continue;
    tree[prevv[v]].emplace_back(graph[prevv[v]][preve[v]]);
  }
}

// LCA
vector<vector<int>> parent;
vector<int> depth;
int logN;
void dfs(int u, int p, int d) {
  parent[0][u] = p;
  depth[u] = d;
  for(edge& e : tree[u]) {
    if(e.to != p) dfs(e.to, u, d+1);
  }
}
void initLCA() {
  logN = 1;
  while((1<<logN) <= N) logN++;
  parent.resize(logN, vector<int>(N, -1));
  depth.resize(N);

  dfs(T, -1, 0);
  for(int i = 0; i+1 < logN; i++) {
    for(int v = 0; v < (int)parent.size(); v++) {
      if(parent[i][v] < 0) parent[i+1][v] = -1;
      else parent[i+1][v] = parent[i][parent[i][v]];
    }
  }
}
int getLCA(int u, int v) {
  if(depth[u] > depth[v]) swap(u, v);
  for(int i = 0; i < logN; i++) {
    if((depth[v]-depth[u])>>i & 1) v = parent[i][v];
  }
  if(u == v) return u;
  for(int i = logN-1; i >= 0; i--) {
    if(parent[i][u] != parent[i][v]) u = parent[i][u], v = parent[i][v];
  }
  return parent[0][u];
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
  buildShortestPathTree();
  initLCA();
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
