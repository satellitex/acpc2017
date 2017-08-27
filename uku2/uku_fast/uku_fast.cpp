#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int inf = 1<<25;

using Pi = pair<int, int>;

struct edge {
  int to, cap, cost, rev;
  edge(){}
  edge(int to, int cap, int cost, int rev)
    :to(to), cap(cap), cost(cost), rev(rev){}
};

using Graph = vector< vector<edge> >;

struct SSSP {
  Graph graph;
  vector<int> mincost, prevv, preve, h;
  SSSP(int V):graph(V), mincost(V), prevv(V), preve(V), h(V){}
  void add_edge(int from, int to, int cap, int cost) {
    graph[from].emplace_back(to, cap, cost, graph[to].size());
    graph[to].emplace_back(from, 0, -cost, graph[from].size()-1);
  }
  int min_cost_flow(int s, int t, int f) {
    int V = graph.size();
    int res = 0;
    fill(h.begin(), h.end(), 0);
    for(int v = 0; v < V; v++) {
      for(int i = 0; i < (int)graph[v].size(); i++) {
	edge& e = graph[v][i];
	if(e.cap > 0) {
	  h[e.to] = min(h[e.to], h[v]+e.cost);
	}
      }
    }
    while(f > 0) {
      priority_queue<Pi, vector<Pi>, greater<Pi> > que;
      fill(mincost.begin(), mincost.end(), inf);
      mincost[s] = 0;
      que.emplace(0, s);
      while(!que.empty()) {
	Pi p = que.top(); que.pop();
	int v = p.second;
	if(mincost[v] < p.first) continue;
	for(int i = 0; i < (int)graph[v].size(); i++) {
	  edge& e = graph[v][i];
	  int cost = mincost[v]+e.cost+h[v]-h[e.to];
	  if(e.cap > 0 && cost < mincost[e.to]) {
	    mincost[e.to] = cost;
	    prevv[e.to] = v; preve[e.to] = i;
	    que.emplace(cost, e.to);
	  }
	}
      }
      if(mincost[t] == inf) return inf;
      for(int v = 0; v < V; v++) h[v] += mincost[v];
      int d = f;
      for(int v = t; v != s; v = prevv[v]) {
	d = min(d, graph[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d*h[t];
      for(int v = t; v != s; v = prevv[v]) {
	edge& e = graph[prevv[v]][preve[v]];
	e.cap -= d;
	graph[e.to][e.rev].cap += d;
      }
    }
    return res;
  }
};

#define MAX_N 100
#define MAX_M 100

int N, M;
int l[MAX_M], b[MAX_M];
int p[MAX_N][MAX_M];

int main() {
  cin >> N >> M;
  for(int i = 0; i < M; i++) cin >> l[i];
  for(int i = 0; i < M; i++) cin >> b[i];
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) cin >> p[i][j];
  }

  int s = N+M*2, t = s+1, V = t+1;
  SSSP graph(V);
  for(int i = 0; i < N; i++) {
    graph.add_edge(s, i, 1, 0);
    for(int j = 0; j < M; j++) {
      if(p[i][j] == -1) continue;
      graph.add_edge(i, N+j, 1, -p[i][j]);
    }
    graph.add_edge(i, t, 1, 0);
  }
  for(int i = 0; i < M; i++) {
    graph.add_edge(N+i, t, l[i]-1, 0);
    graph.add_edge(N+M+i, t, 1, 0);
    graph.add_edge(N+i, N+M+i, 1, -b[i]);
  }

  cout << -graph.min_cost_flow(s, t, N) << endl;

  return 0;
}
