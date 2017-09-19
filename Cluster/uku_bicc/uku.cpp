#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <set>

using namespace std;

#define int long long

using Pi = pair<int, int>;
using vint = vector<int>;
using Graph = vector<vint>;

struct BICC {
  vint ord, low, art, stk, id;
  vector<vint> cmp;
  BICC(){}
  void init(const Graph& graph) {
    int n = graph.size();
    ord.clear(); ord.resize(n, -1);
    low.clear(); low.resize(n, -1);
    art.clear(); art.resize(n, 0);
    cmp.clear();
    id.clear(); id.resize(n, -1);
  }
  void dfs(const Graph& graph, int u, int p, int& k, vint& vis) {
    vis[u] = 1;
    ord[u] = low[u] = k++;
    stk.push_back(u);
    for(int v : graph[u]) {
      if(!vis[v]) {
	dfs(graph, v, u, k, vis);
	low[u] = min(low[u], low[v]);
	if(ord[u] <= low[v]) {
	  art[u] = (ord[u] > 0 || ord[v] > 1);
	  cmp.push_back({u});
	  while(cmp.back().back() != v) {
	    cmp.back().push_back(stk.back());
	    stk.pop_back();
	  }
	}
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
  }
  Graph build(const Graph& graph) { // build the block cut tree
    init(graph);
    int n = graph.size(), k = 0;
    vint vis(n, 0);
    for(int u = 0; u < n; u++) {
      if(ord[u] == -1) dfs(graph, u, -1, k = 0, vis);
    }

    Graph tree(0);
    int sz = 0;
    for(int u = 0; u < n; u++) {
      if(art[u]) {
	tree.push_back({});
	id[u] = sz++;
      }
    }
    for(int i = 0; i < (int)cmp.size(); i++) {
      tree.push_back({});
      int node = sz++;
      for(int u : cmp[i]) {
	if(!art[u]) id[u] = node;
	else {
	  tree[node].push_back(id[u]);
	  tree[id[u]].push_back(node);
	}
      }
    }
    return tree;
  }
  bool isarticulation(int u) {
    return art[u];
  }
  int find(int u) {
    return id[u];
  }
};

#define MAX_N 100000

int N, M, Q;
vint w;

Graph graph, tree;
BICC bicc;

//int sum[MAX_N];
//int maxi[MAX_N];
vint sum;
vint maxi;
void dfs(int u, int p) {
  for(int v : tree[u]) {
    if(v == p) continue;
    dfs(v, u);
    sum[u] += sum[v];
    maxi[u] = max(maxi[u], sum[v]);
  }
}
void solve() {
  if(tree.empty()) return;
  sum.resize(tree.size());
  maxi.resize(tree.size());
  for(int i = 0; i < N; i++) {
    sum[bicc.find(i)] += w[i];
  }
  dfs(0, -1);
}

signed main() {
  cin >> N >> M;
  w.resize(N);
  int all = 0;
  for(int i = 0; i < N; i++) {
    cin >> w[i];
    all += w[i];
  }
  graph.resize(N);
  for(int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v; --u, --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  tree = bicc.build(graph);
  /*
  for(int i = 0; i < N; i++) cout << i << " " << bicc.find(i) << endl;
  for(int i = 0; i < (int)tree.size(); i++) {
    cout << i << ":";
    for(int v : tree[i]) cout << v << " ";
    cout << endl;
  }
  */
  solve();
  for(int i = 0; i < N; i++) {
    if(bicc.isarticulation(i)) {
      int id = bicc.find(i);
      cout << max(all-sum[id], maxi[id]) << endl;
    } else {
      cout << all-w[i] << endl;
    }
  }

  return 0;
}
