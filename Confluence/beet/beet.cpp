#include<bits/stdc++.h>
using namespace std;
#define int long long

typedef pair<int,int> P;
vector<int> dijkstra(int s,vector<vector<P> > & G){
  int n=G.size();
  int INF=1LL<<55LL;
  vector<int> d(n,INF);
  priority_queue<P,vector<P>,greater<P> > q;
  d[s]=0;
  q.push(P(d[s],s));
  while(!q.empty()){
    P p=q.top();q.pop();
    int v=p.second;
    if(d[v]<p.first) continue;
    for(P e:G[v]){
      int u=e.first,c=e.second;
      if(d[u]>d[v]+c){
	d[u]=d[v]+c;
	q.push(P(d[u],u));
      }
    }
  }
  return d;
}

signed main(){
  int n,m,t;
  cin>>n>>m>>t;
  t--;
  vector<vector<P> > G(n);
  for(int i=0;i<m;i++){
    int a,b,c;
    cin>>a>>b>>c;
    a--;b--;
    G[a].push_back(P(b,c));
    G[b].push_back(P(a,c));
  }
  int q;
  cin>>q;
  auto dt=dijkstra(t,G);
  for(int i=0;i<q;i++){
    int u,v;
    cin>>u>>v;
    u--;v--;    
    auto du=dijkstra(u,G);
    auto dv=dijkstra(v,G);
    int ans=max(du[t],dv[t]);
    for(int i=0;i<n;i++){
      if(du[t]!=du[i]+dt[i]) continue;
      if(dv[t]!=dv[i]+dt[i]) continue;
      ans=min(ans,max(du[i],dv[i]));
    }
    cout<<ans<<endl;
  }
  return 0;
}
