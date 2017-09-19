#include <bits/stdc++.h>
#define int long long
#define N 100010
#define V_MAX 100010
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

class Bridges{
public:
  typedef pair<int,int> P;
  int V;                 //ノード数
  vector<vector <int> >G;  //グラフの隣接リストを表現
  set <P> bridges;        // 橋
  int ord[V_MAX];         //行きかけ順をあわらす。
  int low[V_MAX];         //
 
  Bridges(){V = -1;}
  Bridges(int V):G(V){this->V = V;}
   
  void add_edge(int a,int b){
    assert(a < V && b < V);
    G[a].push_back(b);
    G[b].push_back(a);
  }
 
  void dfs(int u, int p, int &c){
    ord[u] = low[u] = c++;
    for(int v:G[u]){
      if(v == p)continue;
      if(ord[v] == -1){
        dfs(v,u,c);
        low[u] = min(low[u],low[v]);
      }
      else low[u] = min(low[u], ord[v]);
      if(ord[u] < low[v]) bridges.insert(P(min(u,v),max(u,v)));
    }
  }
  
  void bridge(){
    assert(V >= 0 && "Set number of node V");
    bridges.clear();
    int c = 0;
    memset(ord,-1,sizeof(ord));
    memset(low,0,sizeof(low));
    for(int i=0;i<V;i++) if(ord[i]==-1) dfs(i,-1,c);
  }
   
  bool isBridge(int u,int v){return bridges.count(P(u,v)) || bridges.count(P(v,u));}
};

class BCC{
public:
  int V;                     // 頂点数
  int K;                     // 分解後の頂点数
  Bridges B;                 // 橋の列挙用
  vector<vector<int> > G;    // 元のグラフ
  vector<vector<int> > T;    // 分解後のグラフ(木)
  vector<int> par;           // 分解後のグラフの頂点0を根としたときの親
  vector<int> cmp;           // 元のグラフの分解後の頂点番号
  vector<int> used;          // dfs用
  
  BCC():V(-1){}
  BCC(int V):V(V),B(V),G(V){};
  
  void add_edge(int a,int b){B.add_edge(a,b);G[a].push_back(b),G[b].push_back(a);}
  
  void dfs(int pos){
    if(used[pos]++) return;
    cmp[pos] = K;
    for(int nx:G[pos]) if(!B.isBridge(pos,nx)) dfs(nx);
  }
  
  int bcc(bool makeT = 0){
    B.bridge();
    used.clear();used.resize(V,0);
    cmp.clear();cmp.resize(V,0);
    K = 0;
    for(int i=0;i<V;i++) if(used[i]==0) dfs(i),K++;
    if( makeT ) makeTree();
    return K;
  }
  
  void makeTree(int pos=0,int pre=-1){
    if(pre == -1){
      T.clear(); T.resize(V);
      par.clear();par.resize(V,-1);
      for(int i=0;i<V;i++){
        set<int> used;
        for(int nx:G[i]){
          int a = cmp[i], b = cmp[nx];
          if(a != b && !used.count(b)) T[a].push_back(cmp[nx]),used.insert(b);
        }
      }
    }
    par[pos] = pre;
    for(int nx:T[pos]) if(nx!=pre) makeTree(nx,pos);
  }
};

vector<vector<int> > G,bG;
vector<int> par;
int n, val[N], sum[N];


int w1[N];
int dfs1(int pos=0,int pre=-1){
  w1[pos] = sum[pos];
  for(int nx:bG[pos]) if(nx != pre) w1[pos] += dfs1(nx, pos);
  return w1[pos];
}

int w2[N];
void dfs2(int pos=0,int pre=-1,int v=0){
  w2[pos] = v;
  for(int nx:bG[pos]) if(nx != pre) dfs2(nx, pos, v + w1[pos] - w1[nx]);
}

BCC bcc;
int ans[N];
void calcAns(){

  for(int i=0;i<n;i++){
    int a = bcc.cmp[i];
    int s = sum[n] - val[i];
    Max(ans[i], max(val[i],sum[a] - val[i]));
    
    //cout<<"i="<<i<<" a="<<a<<" ans[i]="<<ans[i]<<endl;
    for(int to:G[i]){
      int b = bcc.cmp[to];
      if(a == b) continue;
      //cout<<"to="<<to<<" b="<<b<<" w1="<<w1[b]<<" w2="<<w2[a]<<endl;
      if(par[a] != b) Max(ans[i],w1[b]), s -= w1[b];
      else  Max(ans[i],w2[a]), s -= w2[a];
    }
    Max(ans[i],s);
  }
}

signed main(){
  int m;
  cin>>n>>m;
  for(int i=0;i<n;i++) scanf("%lld",&val[i]),sum[n] += val[i];

  bcc = BCC(n);  
  for(int i=0,a,b;i<m;i++) scanf("%lld %lld",&a,&b), bcc.add_edge(a-1,b-1);
  
  bcc.bcc(1);
  G = bcc.G;
  bG = bcc.T;
  par = bcc.par;
  for(int i=0;i<n;i++) sum[bcc.cmp[i]] += val[i];

  dfs1();
  dfs2();
  calcAns();
 
  int q;
  cin>>q;
  while(q--){
    int x;
    scanf("%lld",&x);
    printf("%lld\n",ans[x-1]);
  }
  
  return 0;
}
