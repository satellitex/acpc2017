#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

#define int long long

using Pi = pair<int, int>;
using vint = vector<int>;
using Graph = vector<vint>;

struct BICC {
  Graph graph;
  set<Pi> edges, bridge;
  vint ord, low, cmp;
  set<int> apt;
  vector<vint> nodes;
  BICC(){}
  void init(int V) {
    graph.clear(); graph.resize(V);
    ord.clear(); ord.resize(V);
    low.clear(); low.resize(V);
    cmp.clear(); cmp.resize(V, -1);
  }
  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
    edges.emplace(minmax(u, v));
  }
  void dfs(int u, int p, int& k, vint& vis) {
    vis[u] = 1;
    ord[u] = low[u] = k++;
    bool is_apt = false;
    int cnt = 0;
    for(int& v : graph[u]) {
      if(!vis[v]) {
	cnt++;
	dfs(v, u, k, vis);
	low[u] = min(low[u], low[v]);
	if(~p && ord[u] <= low[v]) is_apt = true;
	if(ord[u] < low[v]) bridge.emplace(minmax(u, v));
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }

    if(p == -1 && cnt > 1) is_apt = true;
    if(is_apt) apt.insert(u);
  }
  void dfs2(int u, int k, vint& vec, vint& vis) {
    if(vis[u]) return;
    vis[u] = 1;
    cmp[u] = k;
    vec.push_back(u);
    for(int& v : graph[u]) {
      if(bridge.count(minmax(u, v))) continue;
      dfs2(v, k, vec, vis);
    }
  }
  int build() {
    int V = graph.size();
    int k = 0;
    vint vis(V, 0);
    dfs(0, -1, k, vis);
    int num = 0;
    vis.clear();
    vis.resize(V, 0);
    {
      vint vec;
      dfs2(0, num++, vec, vis);
      nodes.push_back(vec);
    }
    for(Pi e : bridge) {
      if(cmp[e.first] == -1) {
	vint vec;
	dfs2(e.first, num++, vec, vis);
	nodes.push_back(vec);
      }
      if(cmp[e.second] == -1) {
	vint vec;
	dfs2(e.second, num++, vec, vis);
	nodes.push_back(vec);
      }
    }
    return num;
  }
};

struct SegmentTree {
  vint sum;
  int sz;
  SegmentTree(int n) {
    sz = 1; while(sz < n) sz *= 2;
    sum.resize(2*sz-1, 0);
  }
  void set(int k, int x) {
    k += sz-1;
    sum[k] = x;
    while(k > 0) {
      k = (k-1)/2;
      sum[k] = sum[2*k+1]+sum[2*k+2];
    }
  }
  int Sum(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b) return sum[k];
    int vl = Sum(a, b, 2*k+1, l, (l+r)/2);
    int vr = Sum(a, b, 2*k+2, (l+r)/2, r);
    return vl+vr;
  }
  int Sum(int a, int b) {
    return Sum(a, b, 0, 0, sz);
  }
};

int N, M, Q;
vint w;

int CCV;
BICC bicc;
vint bi4nd, ei4nd;
vint bi4cc, ei4cc;
vint par;
int idx;
void init() {
  idx = 0;
  bi4nd.clear(); bi4nd.resize(N);
  ei4nd.clear(); ei4nd.resize(N);
  bi4cc.clear(); bi4cc.resize(CCV);
  ei4cc.clear(); ei4cc.resize(CCV);
  par.clear(); par.resize(N, -1);
}
void dfs(int u, int p) {
  bi4cc[bicc.cmp[u]] = idx++;
  par[u] = p;
  for(int& id : bicc.nodes[bicc.cmp[u]]) {
    if(bicc.apt.count(id)) bi4nd[id] = idx;
    for(int& v : bicc.graph[id]) {
      if(!bicc.bridge.count(minmax(id, v))) continue;
      if(bicc.cmp[v] == bicc.cmp[p]) continue;
      dfs(v, id);
    }
    if(bicc.apt.count(id)) ei4nd[id] = idx;
  }
  ei4cc[bicc.cmp[u]] = idx;
}

signed main() {
  cin >> N >> M;
  w.resize(N);
  for(int i = 0; i < N; i++) cin >> w[i];
  bicc.init(N);
  for(int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    bicc.add_edge(u, v);
  }
  CCV = bicc.build();
  vint sumw(CCV);
  int all = 0;
  for(int i = 0; i < N; i++) {
    sumw[bicc.cmp[i]] += w[i];
    all += w[i];
  }
  init();
  dfs(0, -1);
  SegmentTree seg(CCV);
  for(int i = 0; i < CCV; i++) {
    seg.set(bi4cc[i], sumw[i]);
  }
  vint maxi(N);
  for(int i = 0; i < N; i++) {
    if(!bicc.apt.count(i)) continue;
    for(int& v : bicc.graph[i]) {
      if(bi4cc[bicc.cmp[i]] > bi4cc[bicc.cmp[v]]) continue;
      int m = seg.Sum(bi4cc[bicc.cmp[v]], ei4cc[bicc.cmp[v]]);
      if(bicc.cmp[i] == bicc.cmp[v]) {
	m -= seg.Sum(bi4nd[i], ei4nd[i])+w[i];
      }
      maxi[i] = max(maxi[i], m);
    }
  }
  cin >> Q;
  while(Q--) {
    int x;
    cin >> x;
    --x;
    if(bicc.apt.count(x)) {
      int ans1 = seg.Sum(0, CCV);
      if(bicc.bridge.count(minmax(par[x], x))) ans1 -= seg.Sum(bi4cc[bicc.cmp[x]], ei4cc[bicc.cmp[x]]);
      else ans1 -= seg.Sum(bi4nd[x], ei4nd[x])+w[x];
      int ans2 = w[x];
      int ans3 = maxi[x];
      cout << max({ans1, ans2, ans3}) << endl;
    } else {
      cout << all - w[x] << endl;
    }
  }


  return 0;
}
