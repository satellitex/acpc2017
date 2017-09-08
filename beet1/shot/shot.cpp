#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back 
#define mp make_pair
#define fr first
#define sc second
#define Rep(i, n) for( int i = 0; i < (n); i++ )
#define Rrep(i, a, n) for( int i = (a); i < (n); i++ )
#define All(v) v.begin(), v.end()

typedef pair<int, int> Pii; 
typedef pair<int, Pii> Pip;
const int INF = 1107110711071107;
const int MAX_N = 5001;

struct BipartiteMatching{
  vector<vector<int> > G;
  int V;
  vector<int> match,used;
  
  BipartiteMatching(){}
  BipartiteMatching(int V):V(V){init();}
  
  void init(){
    for(int i=0;i<(int)G.size();i++) G[i].clear();
    G.clear();
    match.clear();
    used.clear();
    G.resize(V);
    match.resize(V);
    used.resize(V);
    fill(match.begin(),match.end(),-1);
    fill(used.begin(),used.end(),0);
  }
  
  void add_edge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
  }

  bool dfs(int v){
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++){
      int u=G[v][i],w=match[u];
      if(w<0||(!used[w]&&dfs(w))){
	match[v]=u;
	match[u]=v;
	return true;
      }
    }
    return false;
  }

  int bipartite_matching(){
    int res=0;
    for(int v=0;v<V;v++){
      if(match[v]<0){
	if(dfs(v)){
	  res++;
	}
      }
    }
    return res;
  }
};

signed main(){
  int N;
  BipartiteMatching bm(2*MAX_N);
  bool color[MAX_N];
  color[0] = 0;

  cin >> N;
  int sum = 0;
  Rrep(i, 1, N+1) {
    int p; cin >> p;
    if ( !color[p] ) {
      bm.add_edge(p, MAX_N+i);
      color[i] = true;
    } else {
      bm.add_edge(i, MAX_N+p);
      color[i] = false;
    }
    sum += bm.bipartite_matching();
    cout << sum << endl;
  }
  
  return 0;
}
