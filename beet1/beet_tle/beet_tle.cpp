#include<bits/stdc++.h>
using namespace std;
#define int long long

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

  int calc(){
    int res=0;
    fill(match.begin(),match.end(),-1);
    for(int v=0;v<V;v++){
      if(match[v]<0){
	fill(used.begin(),used.end(),0);
	if(dfs(v)){
	  res++;
	}
      }
    }
    return res;
  }
};


signed main(){
  int n;
  cin>>n;
  BipartiteMatching bm(n+1);
  for(int i=1;i<=n;i++){
    int p;
    cin>>p;
    bm.add_edge(p,i);
    cout<<bm.calc()<<endl;
  }
  return 0;
}
