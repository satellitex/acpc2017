#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int inf = 1<<25;

struct edge {
  int to, cap, rev;
  edge(){}
  edge(int to, int cap, int rev):to(to), cap(cap), rev(rev){}
};

using Graph = vector<vector<edge>>;

struct Dinic {
  Graph graph;
  vector<int> level, iter;
  Dinic(int V):graph(V), level(V), iter(V){}
  void add_edge(int from, int to, int cap) {
    graph[from].emplace_back(to, cap, graph[to].size());
    graph[to].emplace_back(from, 0, graph[from].size()-1);
  }
  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(edge& e : graph[v]) {
	if(e.cap > 0 && level[e.to] < 0) {
	  level[e.to] = level[v]+1;
	  que.push(e.to);
	}
      }
    }
    return level[t] >= 0;
  }
  int dfs(int v, int t, int f) {
    if(v == t) return f;
    for(int& i = iter[v]; i < (int)graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(e.cap > 0 && level[e.to] > level[v]) {
	int d = dfs(e.to, t, min(f, e.cap));
	if(d > 0) {
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int s, int t) {
    int flow = 0;
    while(bfs(s, t)) {
      fill(iter.begin(), iter.end(), 0);
      int f;
      while((f = dfs(s, t, inf)) > 0) flow += f;
    }
    return flow;
  }
};

#define MAX_N 5000

int N;
int color[MAX_N+1];

int main() {
  cin >> N;

  int s = N+1, t = s+1, V = t+1;
  Dinic graph(V);
  graph.add_edge(s, 0, 1);
  int ans = 0;
  for(int i = 1; i <= N; i++) {
    int p;
    cin >> p;
    color[i] = 1-color[p];
    if(color[i]) {
      graph.add_edge(i, t, 1);
      graph.add_edge(p, i, 1);
    } else {
      graph.add_edge(s, i, 1);
      graph.add_edge(i, p, 1);
    }
    ans += graph.max_flow(s, t);
    cout << ans << endl;
  }

  return 0;
}
