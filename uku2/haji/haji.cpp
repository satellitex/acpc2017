#include <bits/stdc++.h>
#define int long long
#define N 10010
#define MAX_V 10010
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

/*最小費用流(ワーシャルフロイド使用) O(F|V||E|)*/

//辺を表す構造体(行き先、容量、コスト、逆辺)
struct edge{int to, cap,cost,rev;};
int V=-1;                         //頂点数
vector<edge> G[MAX_V];         //グラフの隣接リスト表現
int dist[MAX_V];               //最短距離
int prevv[MAX_V],preve[MAX_V]; //直前の頂点と辺

// fromからtoへ向かう容量cap、コストcostの辺をグラフに追加する。
void add_edge(int from,int to,int cap=1,int cost=0){
  G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
  G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
}

//sからtへの流量fの最小費用流を求める
//流せない場合-1を返す
int min_cost_flow(int s,int t,int f){
  assert(V >= 0);
  int res=0;
  while(f>0){
    //ベルマンフォード法により,s-t間最短路を求める
    fill(dist,dist+V,INF);
    dist[s]=0;
    bool update = true;
    while(update){
      update = false;
      for(int v=0; v<V ;v++){
        if(dist[v]==INF) continue;
        for(int i=0; i<G[v].size(); i++){
          edge &e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v]+e.cost) {
            dist[e.to] = dist[v] + e.cost;
            prevv[e.to] = v;
            preve[e.to] = i;
            update = true;
          }
        }
      }
    }
    if(dist[t]==INF) return -1; //これ以上流せない。
    
    //s−t間短路に沿って目一杯流す
    int d = f;
    for(int v=t; v!=s; v=prevv[v])d=min(d,G[prevv[v]][preve[v]].cap);

    f -= d;
    res += d*dist[t];
    for(int v=t; v!=s; v=prevv[v]){
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}

signed main(){
  int n,m;
  cin>>n>>m;
  // 0 ~ N :  student  node
  // N ~ N+M : normal stage node
  // N+M ~ N+2*M :  bonus stage node
  
  V = n+2*m + 2;
  const int S =V-1 ,T = S - 1;
  int cap[N],bonus[N];
  for(int i=0;i<m;i++) scanf("%lld",&cap[i]);
  for(int i=0;i<m;i++) scanf("%lld",&bonus[i]);
  
  for(int i=0;i<n;i++){
    add_edge(S,i);
    add_edge(i,T);
    for(int j=0,p;j<m;j++){
      scanf("%lld",&p);
      if(p == -1) continue;
      add_edge(i,n+j,1, - p);
      add_edge(i,n+m+j,1,-bonus[j] - p);
    }
  }

  for(int i=0;i<m;i++) if(cap[i]-1) add_edge(n+i,T,cap[i]-1);
  for(int i=0;i<m;i++) if(cap[i]) add_edge(n+m+i,T,1);
  cout<<-min_cost_flow(S,T,n)<<endl;
  
  return 0;
}
