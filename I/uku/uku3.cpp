#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define MAX_N 100000

using Pi = pair<int, int>;
using vint = vector<int>;
using Graph = vector<vint>;

namespace BICC {
  vint low, ord, cmp;
  set<int> apt;
  set<Pi> brge;
  int root;
  void init(const Graph& g) {
    int n = g.size();
    low.clear();
    low.resize(n);
    ord.clear();
    ord.resize(n);
    cmp.clear();
    cmp.resize(n, -1);
    root = 0;
    while(root < n && g[root].size() == 1) root++;
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
      if(!isbridge(u, v)) fillcmp(g, v, k);
    }
  }
  Graph build(const Graph& g) {
    init(g);
    int n = g.size(), k = 0;
    vint vis(n, 0);
    cout<<"FILL"<<endl;
    dfs(g, root, -1, k, vis);
    cout<<"FILL"<<endl;
    int sz = 0;
    fillcmp(g, root, sz++);
    for(auto&& e : brge) {
      int u = e.first, v = e.second;
      if(cmp[u] == -1) fillcmp(g, u, sz++);
      if(cmp[v] == -1) fillcmp(g, v, sz++);
    }
    cout<<"FILL"<<endl;
    Graph t(sz);
    for(auto&& e : brge) {
      int u = e.first, v = e.second;
      assert(~cmp[u] && ~cmp[v]);
      t[cmp[u]].push_back(cmp[v]);
      t[cmp[v]].push_back(cmp[u]);
    }
    return t;
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
int par[MAX_N];
int sumc[MAX_N];
void dfs(int u, int p) {
  par[u] = p;
  for(int& v : tree[u]) {
    if(v == p) continue;
    dfs(v, u);
    sumc[u] += sumc[v];
  }
}
set<int> st[MAX_N];
void solve() {
  for(auto&& e : BICC::brge) {
    int u = e.first, v = e.second;
    st[BICC::find(u)].insert(v);
    st[BICC::find(v)].insert(u);
  }
  for(int i = 0; i < N; i++) {
    sumv[i] = w[i];
    sumc[BICC::find(i)] += w[i];
  }
  memset(par, -1, sizeof(par));
  dfs(BICC::find(BICC::root), -1);
  for(int i = 0; i < N; i++) {
    if(!BICC::isarticulation(i)) continue;
    int u = BICC::find(i);
    for(int& v : tree[u]) {
      if(v == par[u]) continue;
      sumv[i] += sumc[v];
      maxv[i] = max(maxv[i], sumc[v]);
    }
    maxv[i] = max(maxv[i], sumc[u]-sumv[i]);
  }
}

int main() {
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
  cout << "OK"<<endl;
  tree = BICC::build(graph);
  cout << "OK"<<endl;
  solve();
  cin >> Q;
  while(Q--) {
    int x;
    cin >> x; --x;
    if(BICC::isarticulation(x)) {
      int ans = all;
      if(~par[BICC::find(x)] && st[par[BICC::find(x)]].count(x)) ans -= sumc[BICC::find(x)];
      else ans -= sumv[x];
      cout << max({ans, w[x], maxv[x]}) << endl;
    } else {
      cout << all-w[x] << endl;
    }
  }

  return 0;
}
