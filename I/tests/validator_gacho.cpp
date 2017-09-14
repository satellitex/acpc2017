#include <iostream>
#include <vector>
#include <set>
#include "testlib.h"
using namespace std;

typedef pair<int,int> P;

const int MIN_N = 2;
const int MAX_N = 100000;
const int MAX_M = 100000;
const int MIN_w = 1;
const int MAX_w = 1000000;

int N, M, w[MAX_N], u[MAX_M], v[MAX_M];


void input(){
  
  N = inf.readInt(MIN_N, MAX_N, "N");
  
  inf.readSpace();
  
  M = inf.readInt(N-1, min(N*(N-1)/2,MAX_M), "M");
  
  inf.readEoln();
  
    
  for(int i=0;i<N;i++){

    if(i) inf.readSpace();
    
    w[i] = inf.readInt(MIN_w, MAX_w, "w_i");
    
  }

  inf.readEoln();
  
  for(int i=0;i<M;i++){

    u[i] = inf.readInt(1, N, "u_i");

    inf.readSpace();
    
    v[i] = inf.readInt(1, N, "v_i");
    
    inf.readEoln();
    
  }

  inf.readEof();
  
}

vector<int> G[MAX_N];

set<P> used;

bool used2[MAX_N];

void dfs(int x){

  if(used2[x]) return;

  used2[x] = true;

  for(int i=0;i<G[x].size();i++){

    int nx = G[x][i];

    dfs(nx);
    
  }
  
}

void check(){

  for(int i=0;i<M;i++){
    
    ensuref(u[i]!=v[i], "u_i != v_i");

    ensuref(!used.count(P(u[i], v[i])), "(u_i, v_i)!=(u_j, v_j)");
    
    ensuref(!used.count(P(v[i], u[i])), "(u_i, v_i)!=(v_j, u_j)");

    used.insert(P(u[i], v[i]));
    
    G[u[i]-1].push_back(v[i]-1);
    
    G[v[i]-1].push_back(u[i]-1);
    
  }

  dfs(0);

  bool flag = false;

  for(int i=0;i<N;i++)
    if(used2[i] == false) flag = true;

  ensuref(flag == false, "グラフは連結である");
  
}

int main(){
  
  registerValidation();
  
  input();

  check();
  
  return 0;
}
