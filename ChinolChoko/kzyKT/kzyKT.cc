#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef pair<int,int> P;
typedef pair<P,int> PP;
#define N 1001
vector<int> G[N],rG[N],g;
int n,cmp[N],u[N];
  
void add_edge(int x,int y){G[x].push_back(y);rG[y].push_back(x);}
void dfs(int x){
  u[x]=1;
  for(int i=0;i<G[x].size();i++) {
    if(!u[G[x][i]]) dfs(G[x][i]);
  }
  g.push_back(x);
} 
void rdfs(int x,int k){
  u[x]=1,cmp[x]=k;
  for(int i=0;i<rG[x].size();i++) {
    if(!u[rG[x][i]]) rdfs(rG[x][i],k);
  }
}
int scc() {
  memset(u,0,sizeof(u));g.clear();
  for(int i=0; i<n; i++) {
    if(!u[i]) dfs(i);
  }
  memset(u,0,sizeof(u));
  int k=0;
  for(int i=g.size()-1; i>=0; i--) {
    if(!u[g[i]]) rdfs(g[i],k++);
  }
  return k;
}
void init() {
  for(int i=0; i<n; i++) G[i].clear(),rG[i].clear();
  g.clear();
}
int rev(int x) {return (x+n/2)%n;}
int two_sat(vector<P> v) {
  init();
  for(int i=0; i<v.size(); i++) {
    add_edge(v[i].F,rev(v[i].S));
    add_edge(v[i].S,rev(v[i].F));
  }
  scc();
  for(int i=0; i<n/2; i++) {
    if(cmp[i]==cmp[i+n/2]) return 0;
  }
  return 1;
}

int main() {
  int m;
  cin >> n >> m;
  int a[n],b[n];
  for(int i=0; i<n; i++) cin >> a[i];
  for(int i=0; i<n; i++) {
    cin >> b[i];
    b[i]+=a[i];
  }
  n*=2;
  map<PP,int> ma;
  while(m--) {
    int x,y,z,d;
    cin >> x >> y >> z >> d;
    ma[PP(P(x,y),z)]=d;
  }
  vector<P> v;
  for(int i=0; i<n/2; i++) {
    for(int j=i+1; j<n/2; j++) {
      if(ma.count(PP(P(i,j),0))) {
        int d=ma[PP(P(i,j),0)];
        if(abs(a[i]-a[j])>d) v.push_back(P(i,j));
        if(abs(b[i]-a[j])>d) v.push_back(P(rev(i),j));
        if(abs(a[i]-b[j])>d) v.push_back(P(i,rev(j)));
        if(abs(b[i]-b[j])>d) v.push_back(P(rev(i),rev(j)));
      }
      if(ma.count(PP(P(i,j),1))) {
        int d=ma[PP(P(i,j),1)];
        if(abs(a[i]-a[j])<d) v.push_back(P(i,j));
        if(abs(b[i]-a[j])<d) v.push_back(P(rev(i),j));
        if(abs(a[i]-b[j])<d) v.push_back(P(i,rev(j)));
        if(abs(b[i]-b[j])<d) v.push_back(P(rev(i),rev(j)));
      }
    }
  }
  if(two_sat(v)) {
    cout << "YES" << endl;
    for(int i=0; i<n/2; i++)  cout << (cmp[i]<cmp[rev(i)]) << endl;
  } else cout << "NO" << endl;
  return 0;
}
