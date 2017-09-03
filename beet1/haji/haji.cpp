#include <bits/stdc++.h>
#define N 5010
using namespace std;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

class TSort{
public:
  int V;
  vector<set<int> > in,out;
  deque<int> sorted;
  TSort(){V = 0;}
  TSort(int V){
    in.resize(V);
    out.resize(V);
    this->V = V;
  }
  
  void add_edge(int from,int to){
    assert(from < V && to < V);
    out[from].insert(to);
    in[to].insert(from);
  }

  vector<int> visited;
  void dfs_sort(int pos = -1){
    if(pos == -1){
      sorted.clear(),visited.clear(),visited.resize(V,0);
      for(int i=0;i<V;i++) dfs_sort(i);
      return;
    }

    if(visited[pos]++) return;
    for(int nx:out[pos]) dfs_sort(nx);
    sorted.push_front(pos);
  }
};

int n;
vector<int> G[N];
int calc(deque<int>  &sorted){
  int res = 0,used[N]={};
  for(int a:sorted){
    if(!used[a]++) 
      for(int nx:G[a]) if(!used[nx]++) res++;
  }
  return res;
}

signed main(){

  int n;
  cin>>n;
  TSort T(n+1);

  for(int i=1;i<=n;i++) {
    int par;
    scanf("%d",&par);
    T.add_edge(i,par);
    G[i].push_back(par);
    T.dfs_sort();
    printf("%d\n",calc(T.sorted));
  }
  
  return 0;
}
