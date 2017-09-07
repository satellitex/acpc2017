#include <bits/stdc++.h>
#define int long long
#define double long double
#define N 201
#define M 15
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

class SCC{
public:
  int V,K;                      //頂点数, scc後の頂点数
  vector<vector<int> > G;       //グラフの隣接リストの表現
  vector<vector<int> >rG;       //辺の向きを逆にしたグラフ
  vector<vector<int> >DAG;      //scc後のグラフの隣接リストの表現
  vector<vector<int> >rDAG;     //scc後の辺の向きを逆にしたグラフ
  vector<int> vs;               //帰りがけ順の並び
  vector<int>used;              //すでに調べたか
  vector<int> cmp;              //属する強連結成分のトポロジカル順

  void init(){G.resize(V);rG.resize(V);used.resize(V,0);cmp.resize(V,0);}
  SCC(){V = K = -1;}
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

  int scc(bool makeDAG = 0){ //DAGのグラフも作りたかったらmakeDAGを1にする
    used.clear(); used.resize(V,0);
    vs.clear();
    for(int v=0;v<V;v++) if(!used[v]) dfs(v);
  
    used.clear(); used.resize(V,0);
    int &k= K = 0;
    for(int i=vs.size()-1;i>=0;i--)if(!used[vs[i]]) rdfs(vs[i],k++);

    if(makeDAG) DAG = getDAG(G), rDAG = getDAG(rG); //O(ElogE)

    return k;
  }

  vector<vector<int> >getDAG(const vector<vector<int> > &G){
    assert(K>=0);
    vector<vector<int> >res(K);
    for(int from=0;from<V;from++)
      for(int to:G[from]) if(cmp[from]!=cmp[to]) res[cmp[from]].push_back(cmp[to]);
    
    for(int i=0;i<K;i++){
      sort(res[i].begin(),res[i].end());
      res[i].erase(unique(res[i].begin(),res[i].end()),res[i].end());
    }
    return res;
  }
};


int n,m;
double x[2][N],y[2][N];
double fx[M],fy[M];

double dis(double x1,double y1,double x2,double y2){x1 -= x2;y1 -= y2;return sqrt(x1*x1 + y1*y1);}


double dp[M][M][1<<M]; //start,pos,bit
void  DP(){
  
  for(int i=0;i<M;i++)
    for(int j=0;j<M;j++)
      for(int k=0;k<(1<<M);k++) dp[i][j][k] = INF;
  
  for(int i=0;i<m;i++) dp[i][i][1<<i] = 0;

  for(int start=0;start<m;start++)
    for(int bit=0;bit<(1<<m);bit++)
      for(int pos=0;pos<m;pos++)
        if(dp[start][pos][bit] < INF)
          for(int nx=0;nx<m;nx++){
            if(bit>>nx&1) continue;
            double cost = dp[start][pos][bit]+ dis(fx[pos],fy[pos],fx[nx],fy[nx]);
            int nbit = bit | (1<<nx);
            Min(dp[start][nx][nbit],cost);
          }
}

struct dat{
  double cost;
  int u,v;
  int ubit,vbit;
  bool operator < (const dat &a)const{return cost<a.cost;}
  bool operator > (const dat &a)const{return cost>a.cost;}
};


double getCost(int i,int j,int k,int l,int s,int t){
  //cout<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<s<<" "<<t<<endl;
  return dis(x[k][i],y[k][i],fx[s],fy[s]) + dis(x[l][j],y[l][j],fx[t],fy[t]) + dp[s][t][(1<<m)-1];
}


void add_edge(dat a,SCC &scc){
  int u = a.u, v = a.v;
  bool ub = a.ubit, vb = a.vbit; //!(u && v) -> (!u||!v) -> (u ||!v) && (!u || v) 
  if(ub == 0 && vb == 0) scc.add_edge(n+u,v), scc.add_edge(n+v,u);
  if(ub == 0 && vb == 1) scc.add_edge(n+u,n+v), scc.add_edge(v,u);
  if(ub == 1 && vb == 0) scc.add_edge(u,v), scc.add_edge(n+v,n+u);
  if(ub == 1 && vb == 1) scc.add_edge(u,n+v), scc.add_edge(v,n+u);
}

bool check(SCC &scc){
  scc.scc();
  for(int i=0;i<n;i++) if(scc.cmp[i] == scc.cmp[i+n]) return 0;
  return 1;
}

double calc(vector<dat> A){
  SCC scc(n+n);
    for(dat a:A){
      add_edge(a,scc);
      if(!check(scc)) return a.cost;
    }
    return A.back().cost;
}


signed main(){

  cin>>n>>m;
  for(int i=0;i<n;i++) cin>>x[0][i]>>y[0][i]>>x[1][i]>>y[1][i];
  for(int i=0;i<m;i++) cin>>fx[i]>>fy[i];

  DP();

  vector<dat> A;
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++){
      for(int k=0;k<2;k++)
        for(int l=0;l<2;l++){
          if(i == j && k != l) continue;
          double cost = INF;
          for(int s=0;s<m;s++)
            for(int t=0;t<m;t++) Min(cost,getCost(i,j,k,l,s,t));
          A.push_back((dat){cost,i,j,k,l});
        }
      }
  sort(A.begin(),A.end(),greater<dat>());
  printf("%.8Lf\n",calc(A));
    
  return 0;
}
