#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define int long long

#define MAX_N 100000

using Pi = pair<int, int>;
using vint = vector<int>;
using Graph = vector<vint>;

struct BICC {
  vint low, ord, art, cmp;
  set<Pi> brge;
  int root;
  BICC(){}
  void init(const Graph& g) {
    int n = g.size();
    low.clear(); low.resize(n, -1);
    ord.clear(); ord.resize(n, -1);
    cmp.clear(); cmp.resize(n, -1);
    art.clear(); art.resize(n, 0);
    brge.clear();
    root = 0;
    while(root < n-1 && g[root].size() == 1) root++;
  }
  void dfs(const Graph& g, int u, int p, int& k, Graph& t) {
    ord[u] = low[u] = k++;
    bool isart = false;
    int cnt = 0;
    for(auto&& v : g[u]) {
      if(ord[v] == -1) {
	t[u].push_back(v);
	cnt++;
	dfs(g, v, u, k, t);
	low[u] = min(low[u], low[v]);
	if(~p && ord[u] <= low[v]) isart = true;
	if(ord[u] < low[v]) brge.insert(minmax(u, v));
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
    if(p == -1 && cnt > 1) isart = true;
    if(isart) art[u] = 1;
  }
  bool isarticulation(int u) {
    return art[u];
  }
  bool isbridge(int u, int v) {
    return brge.count(minmax(u, v)) > 0;
  }
  Graph build(const Graph& g) {
    init(g);
    int n = g.size(), k = 0;
    Graph t(n);
    dfs(g, root, -1, k, t);
    return t;
  }
};

int N, M, Q;
vint w;

Graph graph, tree;
set<Pi> edge;
BICC bicc;

int sum[MAX_N];
int maxi[MAX_N];
void dfs(int u, int p) {
  for(int v : tree[u]) {
    if(v == p) continue;
    dfs(v, u);
    sum[u] += sum[v];
    maxi[u] = max(maxi[u], sum[v]);
  }
}
void solve() {
  for(int i = 0; i < N; i++) sum[i] = w[i];
  dfs(bicc.root, -1);
  int tmp[MAX_N];
  for(int i = 0; i < N; i++) tmp[i] = sum[i];
  for(int i = 0; i < N; i++) {
    for(int v : tree[i]) {
      if(bicc.ord[i] > bicc.low[v]) sum[i] -= tmp[v];
    }
  }
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
    edge.insert(minmax(u, v));
  }
  tree = bicc.build(graph);
  solve();
  cin >> Q;
  while(Q--) {
    int x;
    cin >> x; --x;
    if(bicc.isarticulation(x)) {
      //cout << w[x] << " " << all << " " << sum[x] << " " << maxi[x] << endl;
      cout << max({w[x], all-sum[x], maxi[x]}) << endl;
    } else {
      cout << max(w[x], all-w[x]) << endl;
    }
  }

  return 0;
}
