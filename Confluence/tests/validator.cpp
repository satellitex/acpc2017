#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int N_MIN = 2;
const int N_MAX = 100000;
const int M_MIN = 1;
const int M_MAX = 100000;
const int C_MIN = 1;
const int C_MAX = 1000000;
const int Q_MIN = 1;
const int Q_MAX = 100;

int N, M, T, Q;
int a[M_MAX], b[M_MAX], c[M_MAX];
int u[Q_MAX], v[Q_MAX];

struct UnionFind {
  vector<int> data;
  UnionFind(){}
  UnionFind(int sz):data(sz, -1){};
  int size(int x) { return -data[find(x)]; }
  int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  int unite(int x, int y)
  {
    x = find(x), y = find(y);
    if(x != y) {
      if(data[x] < data[y]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return -data[x];
  }
};

void input() {
  N = inf.readInt(N_MIN, N_MAX, "N");
  inf.readSpace();
  M = inf.readInt(N-1, min(N*(N-1)/2, M_MAX), "M");
  inf.readSpace();
  T = inf.readInt(1, N, "T");
  inf.readEoln();
  for(int i = 0; i < M; i++) {
    a[i] = inf.readInt(1, N, format("a[%d]", i+1));
    inf.readSpace();
    b[i] = inf.readInt(1, N, format("b[%d]", i+1));
    inf.readSpace();
    c[i] = inf.readInt(C_MIN, C_MAX, format("c[%d]", i+1));
    inf.readEoln();
  }
  Q = inf.readInt(Q_MIN, Q_MAX, "Q");
  inf.readEoln();
  for(int i = 0; i < Q; i++) {
    u[i] = inf.readInt(1, N, format("u[%d]", i+1));
    inf.readSpace();
    v[i] = inf.readInt(1, N, format("v[%d]", i+1));
    inf.readEoln();
  }
  inf.readEof();
}

void check() {
  set<int> stc;
  set<pair<int, int>> ste;
  UnionFind uf(N);
  bool duplicated_cost = false;
  bool multiple_edge = false;
  bool self_loop = false;
  for(int i = 0; i < M; i++) {
    if(a[i] == b[i]) self_loop = true;
    if(ste.count(make_pair(a[i], b[i]))) multiple_edge = true;
    if(stc.count(c[i])) duplicated_cost = true;
    ste.emplace(a[i], b[i]);
    ste.emplace(b[i], a[i]);
    stc.insert(c[i]);
    uf.unite(a[i]-1, b[i]-1);
  }
  ensuref(!duplicated_cost, "Edge Costs are duplicated");
  ensuref(!multiple_edge, "Multiple edges exist");
  ensuref(!self_loop, "Self loop exist");
  ensuref(uf.size(0) == N, "Graph is disconnected");
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
