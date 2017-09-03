#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int main() {
  int n,m,t;
  cin >> n >> m >> t;
  t--;
  vector<P> v[n],g[n];
  for(int i=0; i<m; i++) {
    int x,y,z;
    cin >> x >> y >> z;
    x--,y--;
    v[x].push_back(P(y,z));
    v[y].push_back(P(x,z));
  }
  priority_queue<P,vector<P>,greater<P> > que;
  que.push(P(0,t));
  int d[n];
  fill(d,d+n,1<<30);
  d[t]=0;
  while(!que.empty()) {
    P p=que.top();que.pop();
    int x=p.second,cc=p.first;
    if(d[x]<cc) continue;
    for(int i=0; i<v[x].size(); i++) {
      int y=v[x][i].first,z=v[x][i].second;
      if(d[y]>d[x]+z) {
        d[y]=d[x]+z;
        que.push(P(d[y],y));
        g[y].clear();
        g[y].push_back(P(x,z));
      } else if(d[y]==d[x]+z) g[y].push_back(P(x,z));
    }
  }
  int T;
  cin >> T;
  while(T--) {
    int s[2];
    cin >> s[0] >> s[1];
    s[0]--,s[1]--;
    int c[2][n];
    for(int k=0; k<2; k++) {
      fill(c[k],c[k]+n,1<<30);
      que.push(P(0,s[k]));
      c[k][s[k]]=0;
      while(!que.empty()) {
        P p=que.top();que.pop();
        int x=p.second,cc=p.first;
        if(c[k][x]<cc) continue;
        for(int i=0; i<g[x].size(); i++) {
          int y=g[x][i].first,z=g[x][i].second;
          if(c[k][y]>c[k][x]+z) {
            c[k][y]=c[k][x]+z;
            que.push(P(c[k][y],y));
          }
        }
      }
    }
    int ans=1<<30;
    for(int i=0; i<n; i++) {
      if(c[0][i]!=(1<<30)&&c[1][i]!=(1<<30)) ans=min(ans,max(c[0][i],c[1][i]));
    }
    cout << ans << endl;
  }
  return 0;
}
