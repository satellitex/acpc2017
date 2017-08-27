#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int inf = 1<<25;

// Sccessive Shortest Path(Primal Dual): minimum cost maximum flow
struct PrimalDual {
  struct edge {
    int to, capacity, cost, rev;
    edge(){}
    edge(int to, int capacity, int cost, int rev):to(to), capacity(capacity), cost(cost), rev(rev){}
  };

  vector< vector<edge> > graph;
  vector<int> potential, mincost, prevv, preve;
  PrimalDual(int V):graph(V), potential(V), mincost(V), prevv(V), preve(V){}
  void add_edge(int from, int to, int capacity, int cost) {
    graph[from].push_back(edge(to, capacity, cost, (int)graph[to].size()));
    graph[to].push_back(edge(from, 0, -cost, (int)graph[from].size()-1));
  }
  int min_cost_flow(int source, int sink, int f) {
    int res = 0;
    fill(potential.begin(), potential.end(), 0);
    fill(prevv.begin(), prevv.end(), -1);
    fill(preve.begin(), preve.end(), -1);

    typedef pair<int, int> Pi;
    while(f > 0) {
      priority_queue<Pi, vector<Pi>, greater<Pi> > que;
      fill(mincost.begin(), mincost.end(), inf);
      mincost[source] = 0;
      que.push(Pi(0, source));
      while(!que.empty()) {
	Pi p = que.top(); que.pop();
	int v = p.second;
	if(mincost[v] < p.first) continue;
	for(int i = 0; i < (int)graph[v].size(); i++) {
	  edge& e = graph[v][i];
	  int dual_cost = mincost[v] + e.cost + potential[v] - potential[e.to];
	  if(e.capacity > 0 && dual_cost < mincost[e.to]) {
	    mincost[e.to] = dual_cost;
	    prevv[e.to] = v; preve[e.to] = i;
	    que.push(Pi(mincost[e.to], e.to));
	  }
	}
      }

      if(mincost[sink] == inf) return -1;
      for(int v = 0; v < (int)graph.size(); v++) potential[v] += mincost[v];
      int d = f;
      for(int v = sink; v != source; v = prevv[v]) d = min(d, graph[prevv[v]][preve[v]].capacity);
      f -= d;
      res += d * potential[sink];
      for(int v = sink; v != source; v = prevv[v]) {
	edge& e = graph[prevv[v]][preve[v]];
	e.capacity -= d;
	graph[v][e.rev].capacity += d;
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
  PrimalDual graph(V);
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
