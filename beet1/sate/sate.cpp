#include<bits/stdc++.h>
using namespace std;
typedef complex<double> P;

int N;
int B[5555];
const int INF = (1<<21);
const int MAX = 100000;
const int MAX_V = 10000;
const int S = 5001;
const int T = 5002;


//最大流 Ford-Fulkerson O(F|E|)

struct edge{int to,cap,rev;};

vector<edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to, int cap = 1){
  G[from].push_back((edge){to, cap, G[to].size()});
  G[to].push_back((edge){from, 0, G[from].size()-1});
}

int dfs(int v, int t, int f){
  if(v == t)return f;
  used[v] = true;
  for(int i = 0 ; i < G[v].size() ; i++){
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0){
      int d = dfs(e.to,t,min(f,e.cap));
      if(d > 0){
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s,int t){
  int flow = 0;
  for(;;){
    memset(used,0,sizeof(used));
    int f = dfs(s,t,INF);
    if(f == 0)return flow;
    flow += f;
  }
}


int main(){
  cin >> N;
  add_edge(S,0);
  int res = 0;
  for(int i=1;i<=N;i++){
    int p; cin >> p;
    if( B[p] ) {
      add_edge(S,i);
      add_edge(i,p);
    } else {
      B[i] = 1;
      add_edge(i,T);
      add_edge(p,i);
    }
    res += max_flow(S,T);
    cout << res << endl;
  }

}