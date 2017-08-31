#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <cmath>

using namespace std;

struct SCC {
  vector< vector<int> > graph, rgraph;
  vector<int> cmp;
  SCC(int V):graph(V), rgraph(V), cmp(V, -1){}
  void add_edge(int u, int v) {
    graph[u].push_back(v);
    rgraph[v].push_back(u);
  }
  void dfs(int u, vector<int>& ord, vector<int>& used) {
    if(used[u]) return;
    used[u] = 1;
    for(int& v : graph[u]) dfs(v, ord, used);
    ord.push_back(u);
  }
  void rdfs(int u, int& id) {
    if(~cmp[u]) return;
    cmp[u] = id;
    for(int& v : rgraph[u]) rdfs(v, id);
  }
  int build() {
    int V = graph.size();
    vector<int> ord, used(V, 0);
    for(int u = 0; u < V; u++) dfs(u, ord, used);
    reverse(ord.begin(), ord.end());
    int sz = 0;
    for(int& u : ord) {
      if(cmp[u] == -1) rdfs(u, sz), sz++;
    }
    return sz;
  }
  bool sat2() {
    int V = graph.size();
    for(int i = 0; i < V/2; i++) {
      if(cmp[i] == cmp[i+V/2]) return false;
    }
    return true;
  }
};

#define MAX_N 1000
#define MAX_M 1000000

int n, m;
int a[MAX_N], b[MAX_N], c[MAX_N];
int x[MAX_M], y[MAX_M], z[MAX_M], d[MAX_M];


int main() {
  cin >> n >> m;
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) cin >> b[i];
  for(int i = 0; i < n; i++) c[i] = a[i]+b[i];
  int V = n*2;
  SCC graph(V);
  for(int i = 0; i < m; i++) {
    cin >> x[i] >> y[i] >> z[i] >> d[i];
  }
  for(int i = 0; i < m; i++) {
    int sgn = (z[i] == 0 ? 1 : -1);
    if(sgn*abs(a[x[i]]-a[y[i]]) > sgn*d[i]) {
      graph.add_edge(x[i]+n, y[i]);
      graph.add_edge(y[i]+n, x[i]);
    }
    if(sgn*abs(a[x[i]]-c[y[i]]) > sgn*d[i]) {
      graph.add_edge(x[i]+n, y[i]+n);
      graph.add_edge(y[i], x[i]);
    }
    if(sgn*abs(c[x[i]]-a[y[i]]) > sgn*d[i]) {
      graph.add_edge(x[i], y[i]);
      graph.add_edge(y[i]+n, x[i]+n);
    }
    if(sgn*abs(c[x[i]]-c[y[i]]) > sgn*d[i]) {
      graph.add_edge(x[i], y[i]+n);
      graph.add_edge(y[i], x[i]+n);
    }
  }
  graph.build();
  if(graph.sat2()) {
    cout << "YES" << endl;
    for(int i = 0; i < n; i++) {
      cout << (int)(graph.cmp[i] > graph.cmp[i+n]) << endl;
    }
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
