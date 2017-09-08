#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cfloat>
#include <cstdio>

using namespace std;

using Graph = vector<vector<int>>;

struct SCC {
  int V;
  Graph graph, rgraph;
  vector<int> cmp;
  SCC(int V):V(V), graph(V), rgraph(V), cmp(V, -1){}
  void add_edge(int u, int v) {
    graph[u].push_back(v);
    rgraph[v].push_back(u);
  }
  void dfs(int u, vector<int>& ord, vector<int>& used) {
    if(used[u]) return;
    used[u] = 1;
    for(int v : graph[u]) dfs(v, ord, used);
    ord.push_back(u);
  }
  void rdfs(int u, int id) {
    if(~cmp[u]) return;
    cmp[u] = id;
    for(int v : rgraph[u]) rdfs(v, id);
  }
  int build() {
    vector<int> ord, used(V, 0);
    for(int u = 0; u < V; u++) dfs(u, ord, used);
    reverse(ord.begin(), ord.end());
    int sz = 0;
    for(int u : ord) {
      if(cmp[u] == -1) rdfs(u, sz++);
    }
    return sz;
  }
};

struct SAT2 : SCC {
  int N;
  SAT2(int N):SCC(N*2), N(N){}
  void AorB(int i, int j) {
    add_edge(i+N, j);
    add_edge(j+N, i);
  }
  void nAorB(int i, int j) {
    add_edge(i, j);
    add_edge(j+N, i+N);
  }
  void AornB(int i, int j) {
    add_edge(i+N, j+N);
    add_edge(j, i);
  }
  void nAornB(int i, int j) {
    add_edge(i, j+N);
    add_edge(j, i+N);
  }
  bool sat2() {
    build();
    for(int i = 0; i < N; i++) {
      if(cmp[i] == cmp[i+N]) return false;
    }
    return true;
  }
};

struct P {
  double x, y;
  P(){}
  P(double x, double y):x(x), y(y){}
};
double sq(double x) {
  return x*x;
}
double dist(P a, P b) {
  return sqrt(sq(a.x-b.x)+sq(a.y-b.y));
}

const double inf = DBL_MAX/2;

#define MAX_N 200
#define MAX_M 15

int n, m;
P shop[MAX_N][2];
P fact[MAX_M];

double dp[1<<MAX_M][MAX_M][MAX_M];
double dp2[4][MAX_N][MAX_N];

int main() {
  cin >> n >> m;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < 2; j++)
      cin >> shop[i][j].x >> shop[i][j].y;
  for(int i = 0; i < m; i++)
    cin >> fact[i].x >> fact[i].y;

  for(int i = 0; i < (1<<m); i++)
    for(int j =0; j < m; j++)
      for(int k = 0; k < m; k++)
	dp[i][j][k] = inf;

  for(int i = 0; i < m; i++) {
    dp[1<<i][i][i] = 0;
    for(int bit = 0; bit < (1<<m); bit++) {
      if(!((bit>>i)&1)) continue;
      for(int j = 0; j < m; j++) {
	if(!((bit>>j)&1)) continue;
	for(int k = 0; k < m; k++) {
	  if(((bit>>k)&1) || dp[bit][i][j] == inf) continue;
	  double d = dist(fact[j], fact[k]);
	  dp[bit|(1<<k)][i][k] = min(dp[bit|(1<<k)][i][k], dp[bit][i][j]+d);
	}
      }
    }
  }

  for(int i = 0; i < 4; i++)
    for(int j = 0; j < n; j++)
      for(int k = 0; k < n; k++)
	dp2[i][j][k] = inf;

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < m; k++) {
	for(int l = 0; l < m; l++) {
	  for(int h = 0; h < 4; h++) {
	    double d = dist(shop[i][h&1], fact[k]);
	    double e = dist(fact[l], shop[j][(h>>1)&1]);
	    //printf("%.12f %.12f\n", d, e);
	    dp2[h][i][j] = min(dp2[h][i][j], d+dp[(1<<m)-1][k][l]+e);
	  }
	}
      }
    }
  }

  /*
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < 4; k++) {
	printf("%.12f ", dp2[k][i][j]);
      }
      puts("");
    }
    puts("");
  }
  */

  double lb = 0, ub = 100000;
  for(int i = 0; i < 200; i++) {
    double mb = (lb+ub)/2;
    SAT2 sat2(n);
    for(int j = 0; j < n; j++) {
      for(int k = j+1; k < n; k++) {
	if(dp2[0][j][k] > mb) sat2.AorB(j, k);
	if(dp2[1][j][k] > mb) sat2.nAorB(j, k);
	if(dp2[2][j][k] > mb) sat2.AornB(j, k);
	if(dp2[3][j][k] > mb) sat2.nAornB(j, k);
      }
    }
    if(sat2.sat2()) ub = mb;
    else lb = mb;
  }

  printf("%.12f\n", ub);


  return 0;
}
