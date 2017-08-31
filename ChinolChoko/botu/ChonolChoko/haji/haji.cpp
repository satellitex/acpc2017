#include <bits/stdc++.h>
#define int long long
#define N 1010
#define MAX_V 1010
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}
class SCC{
public:
  int V; //頂点数
  vector<vector<int> > G; //グラフの隣接リストの表現
  vector<vector<int> >rG;//辺の向きを逆にしたグラフ
  vector<int> vs;       //帰りがけ順の並び
  vector<int>used;     //すでに調べたか
  vector<int> cmp;       //属する強連結成分のトポロジカル順

  void init(){rG.resize(V);G.resize(V);used.resize(V,0);cmp.resize(V,0);}
  SCC(){V = -1;}
  SCC(int V):V(V){init();};
  
  void add_edge(int from,int to){
    assert(from<V && to<V);
    G[from].push_back(to);
    rG[to].push_back(from);
  }

  void dfs(int v){
    used[v]=true;
    for(int nx:G[v]) if(!used[nx]) dfs(nx);
    vs.push_back(v);
  }

  void rdfs(int v,int k){
    used[v]=true;
    cmp[v]=k;
    for(int nx:rG[v]) if(!used[nx]) rdfs(nx,k);
  }

  int scc(){
    used.clear(); used.resize(V,0);
    vs.clear();
    for(int v=0;v<V;v++) if(!used[v]) dfs(v);
  
    used.clear(); used.resize(V,0);
    int k=0;
    for(int i=vs.size()-1;i>=0;i--)if(!used[vs[i]]) rdfs(vs[i],k++);
    return k;
  }
};

int A[N],B[N];
bool check(int x,int y,int z,int d,int usex,int usey){
  int X = A[x] + usex*B[x];
  int Y = A[y] + usey*B[y];
  return z? abs(X-Y)>=d:abs(X-Y)<=d;
}

signed main(){
  int n,m;
  cin>>n>>m;
  for(int i=0;i<n;i++) scanf("%lld",&A[i]);
  for(int i=0;i<n;i++) scanf("%lld",&B[i]);
  
  // 0 ~ N: 真ノード
  // N ~ 2*N-1: 偽ノード
  SCC S(2*N);
  for(int i=0;i<m;i++){
    int x,y,z,d;
    scanf("%lld %lld %lld %lld",&x,&y,&z,&d);
    if(!check(x,y,z,d,0,0)) S.add_edge(N+x,y), S.add_edge(N+y,x);
    if(!check(x,y,z,d,0,1)) S.add_edge(N+x,N+y), S.add_edge(y,x);
    if(!check(x,y,z,d,1,0)) S.add_edge(x,y), S.add_edge(N+y,N+x);
    if(!check(x,y,z,d,1,1)) S.add_edge(x,N+y), S.add_edge(y,N+x);
  }

  S.scc();
  for(int i=0;i<n;i++)
    if(S.cmp[i] == S.cmp[N+i]) cout<<"NO"<<endl,exit(0);
  
  cout<<"YES"<<endl;
  for(int i=0;i<n;i++) cout<<(S.cmp[i] > S.cmp[N+i])<<endl;
  
  return 0;
}
