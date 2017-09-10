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

struct UnionFind {
  vint data;
  UnionFind(int n):data(n, -1){}
  int find(int x) {
    return data[x] < 0 ? x : data[x] = find(data[x]);
  }
  int size(int x) {
    return -data[find(x)];
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return false;
    if(data[x] < data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return true;
  }
};

namespace BICC {
  vint low, ord, cmp;
  set<int> apt;
  set<Pi> brge;
  vint par;
  int root;
  void init(const Graph& g) {
    int n = g.size();
    low.clear();
    low.resize(n);
    ord.clear();
    ord.resize(n);
    cmp.clear();
    cmp.resize(n, -1);
    apt.clear();
    brge.clear();
    par.clear();
    root = 0;
    while(root < n-1 && g[root].size() == 1) root++;
  }
  void dfs(const Graph& g, int u, int p, int& k, vint& vis) {
    vis[u] = 1;
    ord[u] = low[u] = k++;
    bool isapt = false;
    int cnt = 0;
    for(auto&& v : g[u]) {
      if(!vis[v]) {
	cnt++;
	dfs(g, v, u, k, vis);
	low[u] = min(low[u], low[v]);
	if(~p && ord[u] <= low[v]) isapt = true;
	if(ord[u] < low[v]) brge.insert(minmax(u, v));
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
    if(p == -1 && cnt > 1) isapt = true;
    if(isapt) apt.insert(u);
  }
  bool isarticulation(int u) {
    return apt.count(u) > 0;
  }
  bool isbridge(int u, int v) {
    return brge.count(minmax(u, v)) > 0;
  }
  void fillcmp(const Graph& g, int u, int k) {
    if(~cmp[u]) return;
    cmp[u] = k;
    for(auto&& v : g[u]) {
      fillcmp(g, v, k);
    }
  }
  Graph build(const Graph& g) {
    init(g);
    int n = g.size(), k = 0;
    vint vis(n, 0);
    dfs(g, root, -1, k, vis);
    int col = 0;
    for(auto&& a : apt) cmp[a] = col++;
    for(auto&& a : apt) {
      for(auto&& v : g[a]) {
	if(~cmp[v]) continue;
	par.push_back(a);
	fillcmp(g, v, col++);
      }
    }
    Graph t(col);
    UnionFind uf(col);
    for(auto&& a : apt) {
      for(auto&& v : g[a]) {
	if(isarticulation(v)) continue;
	if(uf.same(cmp[a], cmp[v])) continue;
	t[cmp[a]].push_back(cmp[v]);
	t[cmp[v]].push_back(cmp[a]);
	uf.unite(cmp[a], cmp[v]);
      }
    }
    for(auto&& a : apt) {
      for(auto&& v : g[a]) {
	if(!isarticulation(v)) continue;
	if(uf.same(cmp[a], cmp[v])) continue;
	t[cmp[a]].push_back(cmp[v]);
	t[cmp[v]].push_back(cmp[a]);
	uf.unite(cmp[a], cmp[v]);
      }
    }
    return t;
  }
  bool isarticulation2(int a) {
    return 0 <= a && a < (int)apt.size();
  }
  int find(int u) {
    return cmp[u];
  }
};

int N, M, Q;
vint w;

Graph graph, tree;
set<Pi> edge;

int sumv[MAX_N];
int maxv[MAX_N];
int sumc[MAX_N];
int maxc[MAX_N];
bool used[MAX_N];
void dfs(int u) {
  used[u] = true;
  for(int& v : tree[u]) {
    if(used[v]) continue;
    dfs(v);
    sumc[u] += sumc[v];
    maxc[u] = max(maxc[u], sumc[v]);
  }
}

void solve() {
  for(int i = 0; i < N; i++) {
    sumc[BICC::find(i)] += w[i];
  }
  if(tree.empty()) return;
  memset(used, false, sizeof(used));
  dfs(BICC::find(BICC::root));
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
  tree = BICC::build(graph);
  for(int i = 0; i < N; i++) cout << i << " " << BICC::find(i) << endl;
  for(int i = 0; i < (int)tree.size(); i++) {
    cout << i << ":";
    for(int& v : tree[i]) cout << v << " ";
    cout << endl;
  }

  solve();
  cin >> Q;
  while(Q--) {
    int x;
    cin >> x; --x;
    if(BICC::isarticulation(x)) {
      int X = BICC::find(x);
      cout << max({w[x], all-sumc[X], maxc[X]}) << endl;
      cout << w[x] << " " << sumc[X] << " " << all-sumc[X] << " " << maxc[X] << endl;
    } else {
      //cout << max(w[x], all-w[x]) << endl;
    }
  }

  return 0;
}
