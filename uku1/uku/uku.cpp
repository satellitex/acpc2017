#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 100000

int N;
vector<int> x;
vector<int> graph[MAX_N];

int dp[2][MAX_N];
// dp[0][u]:=uを含む安定集合の最大重み和
// dp[1][u]:=uを含まない安定集合の最大重み和
int ans[2][MAX_N];

void dfs(int u, int p) {
  for(int v : graph[u]) {
    if(v == p) continue;
    dfs(v, u);
  }

  dp[0][u] = 0;
  dp[1][u] = x[u];
  for(int v : graph[u]) {
    if(v == p) continue;
    dp[0][u] += max(dp[0][v], dp[1][v]);
    dp[1][u] += dp[0][v];
  }
}

void dfs2(int u, int p, int X, int Y) {
  ans[0][u] = dp[0][u]+max(X, Y);
  ans[1][u] = dp[1][u]+X;
  for(int v : graph[u]) {
    if(v == p) continue;
    dfs2(v, u, ans[0][u]-max(dp[0][v], dp[1][v]), ans[1][u]-dp[0][v]);
  }
}

void solve() {
  dfs(0, -1);
  dfs2(0, -1, 0, 0);
  for(int i = 0; i < N; ++i) {
    cout << ans[1][i] << endl;
  }
}

int main() {
  cin >> N;
  x.resize(N);
  for(int i = 0; i < N; ++i) {
    cin >> x[i];
  }
  for(int i = 0; i < N-1; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  solve();

  return 0;
}
