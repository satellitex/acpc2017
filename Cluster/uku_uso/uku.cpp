#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <cstring>

using namespace std;

#define int long long
#define MAX_N 100000

using Pi = pair<int, int>;
using vint = vector<int>;
using Graph = vector<vint>;

int N, M, Q;
vint w;

Graph graph;
set<Pi> edge;

// Biconnected Components
vint low, ord, cmp;
set<int> apt; // 関節点
set<Pi> brge; // 橋
Graph bicc; // 二重辺連結成分を構成する頂点集合
int root; // 葉でない頂点を根とする
void init4bicc() {
  low.clear();
  low.resize(N);
  ord.clear();
  ord.resize(N);
  cmp.clear();
  cmp.resize(N, -1);
  root = 0;
  //while(root < N-1 && graph[root].size() == 1) root++;
}
void dfs4bicc(int u, int p, int& k, vint& vis) {
  vis[u] = 1;
  ord[u] = low[u] = k++;
  bool isapt = false;
  int cnt = 0;
  for(int& v : graph[u]) {
    if(!vis[v]) {
      cnt++;
      dfs4bicc(v, u, k, vis);
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
void fillcmp(int u, int k, vint& vec) {
  if(~cmp[u]) return;
  cmp[u] = k;
  vec.push_back(u);
  for(int& v : graph[u]) {
    if(!brge.count(minmax(u, v))) fillcmp(v, k, vec);
  }
}
int BICC() {
  init4bicc();
  int k = 0;
  vint vis(N, 0);
  dfs4bicc(root, -1, k, vis);
  int num = 0;
  {
    vint vec;
    fillcmp(root, num++, vec);
    bicc.push_back(vec);
  }
  for(Pi e : brge) {
    if(cmp[e.first] == -1) {
      vint vec;
      fillcmp(e.first, num++, vec);
      bicc.push_back(vec);
    }
    if(cmp[e.second] == -1) {
      vint vec;
      fillcmp(e.second, num++, vec);
      bicc.push_back(vec);
    }
  }
  return num;
}

// Tree DP
// 頂点に関する部分木の重み和・最大重み
int sumv[MAX_N];
int maxv[MAX_N];
int par[MAX_N];
// 連結成分に関する部分木の重み和
int sumc[MAX_N];
void dfs(int u, int p) {
  par[u] = p;
  for(int& id : bicc[cmp[u]]) {
    sumv[id] = w[id];
    sumc[cmp[id]] += w[id];
    for(int& v : graph[id]) {
      if((p != -1 && cmp[v] == cmp[p]) || cmp[u] == cmp[v]) continue;
      if(!brge.count(minmax(id, v))) continue;
      dfs(v, id);
      sumv[id] += sumc[cmp[v]];
      sumc[cmp[id]] += sumc[cmp[v]];
      maxv[id] = max(maxv[id], sumc[cmp[v]]);
    }
  }
  for(int& id : bicc[cmp[u]]) {
    maxv[id] = max(maxv[id], sumc[cmp[id]]-sumv[id]);
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
  BICC();
  memset(par, -1, sizeof(par));
  dfs(root, -1);

  for(int x = 0; x < N; x++) {
    if(apt.count(x)) {
      int ans = all;
      if(brge.count(minmax(par[x], x))) ans -= sumc[cmp[x]];
      else ans -= sumv[x];
      ans = max({ans, w[x], maxv[x]});
      cout << ans << endl;
    } else {
      cout << max(all-w[x], w[x]) << endl;
    }
  }

  return 0;
}
