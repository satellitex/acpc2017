#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>

using namespace std;

struct SCC {
  vector< vector<int> > graph, rgraph;
  vector<int> cmp;
  vector< pair<int, int> > edges;
  SCC(int V):graph(V), rgraph(V), cmp(V, -1){}
  void add_edge(int u, int v) {
    graph[u].push_back(v);
    rgraph[v].push_back(u);
    edges.emplace_back(u, v);
  }
  void dfs(int u, int p, vector<int>& ord, vector<int>& used) {
    if(used[u]) return;
    used[u] = 1;
    for(int& v : graph[u]) {
      if(v != p) dfs(v, u, ord, used);
    }
    ord.push_back(u);
  }
  void rdfs(int u, int& id) {
    if(~cmp[u]) return;
    cmp[u] = id;
    for(int& v : rgraph[u]) rdfs(v, id);
  }
  int build(vector< vector<int> >& dag) {
    int V = graph.size();
    vector<int> ord, used(V, 0);
    for(int u = 0; u < V; u++) dfs(u, -1, ord, used);
    reverse(ord.begin(), ord.end());
    int sz = 0;
    for(int u = 0; u < V; u++) {
      if(cmp[u] == -1) rdfs(u, sz), sz++;
    }
    dag.resize(sz);
    set< pair<int, int> > st;
    for(auto& e : edges) {
      int u = cmp[e.first], v = cmp[e.second];
      if(u == v || st.count(make_pair(u, v))) continue;
      dag[u].push_back(v);
      st.emplace(u, v);
    }
    return sz;
  }
};

int n, m;
vector<int> a, b;

int main() {
  cin >> n >> m;
  a.resize(n);
  b.resize(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) cin >> b[i];
  SCC graph(n);
  for(int i = 0; i < m; i++) {
    int x, y, z, d;
    cin >> x >> y >> z >> d;
    if(z == 0) {
    } else {
    }
  }
  return 0;
}
