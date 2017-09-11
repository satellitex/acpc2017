#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back 
#define mp make_pair
#define fr first
#define sc second
#define Rep(i, n) for( int i = 0; i < (n); i++ )
#define Rrep(i, a, n) for( int i = (a); i < (n); i++ )
#define All(v) v.begin(), v.end()

typedef pair<int, int> Pii; 
typedef pair<int, Pii> Pip;
const int INF = 1107110711071107;
const int MAX_N = 100001;

int N, M;
int w[MAX_N];
int dp[MAX_N];
vector<int> graph[MAX_N];
vector<int> tree[MAX_N];
int ord[MAX_N], low[MAX_N];
bool vis[MAX_N];

void dfs(int v, int p, int &k) { // search lowlink and order
  vis[v] = true;
	
  ord[v] = k++;
  low[v] = ord[v];
	
  for ( int i = 0; i < (int)graph[v].size(); i++ ) {
    if ( !vis[graph[v][i]] ) {
      dfs(graph[v][i], v, k);
      tree[v].push_back(graph[v][i]);
      low[v] = min(low[v], low[graph[v][i]]);
    }
    else if ( graph[v][i] != p ) {
      low[v] = min(low[v], ord[graph[v][i]]);
    }
  }
	
}

int tree_dp(int v) { // calc subtree cost
  int sum = w[v];
  for ( int i = 0; i < (int)tree[v].size(); i++ ) {
    sum += tree_dp(tree[v][i]);
  }

  return dp[v] = sum;
}

signed main() {
  cin >> N >> M;
  for ( int i = 0; i < N; i++ ) cin >> w[i];
  for ( int i = 0; i < M; i++ ) {
    int x, y;
    cin >> x >> y;
    graph[--x].push_back(--y);
    graph[y].push_back(x);
  }
	
  int k = 0;
  for ( int i = 0; i < N; i++ ) {
    if ( !vis[i] ) dfs(i, -1, k);
  }

  tree_dp(0);

  for ( int i = 0; i < N; i++ ) {
    int ans = 0;
    int all = dp[0] - dp[i];
    for ( int j = 0; j < (int)tree[i].size(); j++ ) {
      if ( ord[i] <= low[tree[i][j]] ) {	
	ans = max(ans, dp[tree[i][j]]);
      } else {
	all += dp[tree[i][j]];
      }
    }

    cout << max(ans, all) << endl;
  }
  
  return (0);
}
