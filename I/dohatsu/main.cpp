#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;

int const MAX_V = 100001;
int const MAX_E = 200001;
int const INF = 1<<29;
 
vector<int> G[MAX_V];
int ord[MAX_V], low[MAX_V];

vector<int> tree[MAX_V];
ll size[MAX_V];
ll A[MAX_V];

void dfs(int pos){
  size[pos]=A[pos];
  for(int i=0;i<(int)tree[pos].size();i++){
    int to=tree[pos][i];
    dfs(to);
    size[pos]+=size[to];
  }
}

int V,E;
void init();
vector<int> ans;
 
void rec(int pos,int prev,int& k){
  low[pos]=ord[pos]=k++;
  int flg=0,child=0;
  for(int i=0;i<(int)G[pos].size();i++){
    int to=G[pos][i];
    if(to==prev)continue;
    if(ord[to]==-1){
      tree[pos].push_back(to);
          
      child++;
      rec(to,pos,k);
      low[pos]=min(low[pos],low[to]);
      if(low[to]>=ord[pos]&&prev!=-1)flg=true;
    }
    low[pos]=min(low[pos],ord[to]);
  }
  if(prev==-1&&child>=2)flg=true;
  if(flg)ans.push_back(pos);
}
 
void init() {
  ans.clear();
  for(int i=0;i<V;i++){
    low[i]=INF;
    ord[i]=-1;
    G[i].clear();
  }
}

ll total=0;
int vd[MAX_V];
ll mem[MAX_V];

ll solve(int x){
  
  if(vd[x])return mem[x];
  vd[x]=1;

  if(x==0){
    ll res=A[x];
    for(int i=0;i<(int)tree[x].size();i++){
      int to=tree[x][i];
      res=max(res, size[to]);
    }
    return mem[x]=res;
  }
  
  if(!binary_search(ans.begin(),ans.end(),x)){
    mem[x]=max(total-A[x],(ll)A[x]);
    return mem[x];
  }
  
  ll res=A[x];
  ll ps=total-size[x];

  for(int i=0;i<(int)tree[x].size();i++){
    int to=tree[x][i];
    if(low[to]>=ord[x]){
      res=max(res,size[to]);
    }else{
      ps+=size[to];
    }
  }
  res=max(res,ps);
  return mem[x]=res;
}



int main(){
 
  scanf("%d %d",&V,&E);
  init();
  for(int i=0;i<V;i++){
    scanf("%lld",&A[i]);
    total+=A[i];
  }
  
  for(int i=0;i<E;i++){
    int u, v; 
    scanf("%d %d",&u,&v);
    u--,v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }
 
  int k=0;
  for(int i=0;i<V;i++)
    if(ord[i]==-1)
      rec(i,-1,k);
  
  dfs(0);

  sort(ans.begin(),ans.end());

  
  int Q;
  scanf("%d",&Q);
  while(Q--){
    int x;
    scanf("%d",&x);
    x--;

    printf("%lld\n",solve(x));
  }
  
  //for(int i=0;i<V;i++)cout<<low[i]<<' '<<ord[i]<<' '<<i<<endl;

  return 0;
}
