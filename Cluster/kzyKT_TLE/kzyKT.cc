#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef long long ll;
typedef pair<ll,ll> P;

vector<ll> v[111111],v2[111111],dp[111111];
ll a[111111],d[111111],ord[111111],low[111111];
set<P> s;
set<ll> se[111111];

void dfs(int x,int p,int &c,vector<P> &B){
  ord[x]=low[x]=c++;
  for(int i=0;i<v[x].size();i++){
    int y=v[x][i];
    if(y==p) continue;
    if(ord[y]==-1){
      dfs(y,x,c,B);
      low[x]=min(low[x],low[y]);
    } else low[x]=min(low[x],ord[y]);
    if(ord[x]<low[y]) B.push_back(P(x,y));
  }
}

void bridge(int n,vector<P> &B){
  B.clear();
  int c=0;
  fill(ord,ord+n,-1);
  for(int i=0;i<n;i++)if(ord[i]==-1)dfs(i,-1,c,B);
}

int p[100001],r[100001];
void init(){for(int i=0;i<100001;i++)p[i]=i,r[i]=0;}
int find(int x){return (p[x]==x)?x:(p[x]=find(p[x]));}
void unite(int x,int y) {
  x=find(x),y=find(y);
  if(x==y)return;
  if(r[x]<r[y])p[x]=y;
  else{p[y]=x;if(r[x]==r[y])r[x]++;}
}
bool same(int x,int y){return find(x)==find(y);}

ll dfs(ll x,ll p) {
  ll sum=0;
  for(int i=0; i<v2[x].size(); i++) {
    ll y=v2[x][i];
    if(y==p) continue;
    if(dp[x][i]!=-1) sum+=dp[x][i];
    else {
      ll z=dfs(y,x);
      dp[x][i]=z;
      sum+=z;
    }
  }
  return sum+d[x];
}

int main() {
  init();
  ll n,m,T;
  cin >> n >> m;
  for(ll i=0; i<n; i++) cin >> a[i];
  for(ll i=0; i<m; i++) {
    ll x,y;
    cin >> x >> y;
    x--,y--;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  for(int i=0; i<n; i++) {
    sort(v[i].begin(),v[i].end());
    v[i].erase(unique(v[i].begin(),v[i].end()),v[i].end());
  }
  vector<P> g;
  bridge(n,g);
  for(int i=0; i<g.size(); i++) {
    if(g[i].F>g[i].S) swap(g[i].F,g[i].S);
    s.insert(g[i]);
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<v[i].size(); j++) {
      int x=i,y=v[i][j];
      if(x>y) swap(x,y);
      if(s.count(P(x,y))) continue;
      unite(x,y);
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<v[i].size(); j++) se[i].insert(find(v[i][j]));
  }
  for(int i=0; i<n; i++) d[find(i)]+=a[i];
  for(int i=0; i<g.size(); i++) {
    int x=find(g[i].F),y=find(g[i].S);
    v2[x].push_back(y);
    v2[y].push_back(x);
  }
  for(int i=0; i<n; i++) dp[i].resize(v2[i].size(),-1);
  for(int i=0; i<n; i++) dfs(i,-1);
  cin >> T;
  while(T--) {
    int x;
    cin >> x;
    x--;
    ll ans=a[x],ans2=0,xx=find(x);
    for(int j=0; j<v2[xx].size(); j++) {
      ll yy=v2[xx][j];
      if(se[x].count(yy)) ans=max(ans,dp[xx][j]);
      else ans2+=dp[xx][j];
    }
    ans=max(ans,ans2+d[xx]-a[x]);
    cout << ans << endl;
  }
  return 0;
}
