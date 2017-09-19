#include<bits/stdc++.h>
using namespace std;
signed main(){
  int n;
  cin>>n;
  vector<int> G[5555];
  int dp[2][5555];
  function<int(int,int)> dfs=[&](int x,int v){
    if(G[v].empty()) return 0;
    if(~dp[x][v]) return dp[x][v];
    int res=0;
    for(int u:G[v]) res+=dfs(0,u);
    if(x) return dp[x][v]=res;
    int tmp=res;
    for(int u:G[v])
      res=max(res,tmp-dfs(0,u)+dfs(1,u)+1);
    return dp[x][v]=res;
  };
  for(int i=1;i<=n;i++){
    int p;
    cin>>p;
    G[p].push_back(i);
    memset(dp,-1,sizeof(dp));
    cout<<dfs(0,0)<<endl;
  }
  return 0;
}
