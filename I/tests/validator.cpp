#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const long long N_MIN = 1;
const long long N_MAX = 100000;
const long long M_MAX = 100000;
const long long W_MIN = 1;
const long long W_MAX = 1000000;
const long long Q_MIN = 1;
const long long Q_MAX = 100000;

long long N, M, Q;
long long w[N_MAX];
long long u[M_MAX], v[M_MAX];
long long x[Q_MAX];

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
  inf.readEoln();
  for(int i = 0; i < N; i++) {
    if(i) inf.readSpace();
    w[i] = inf.readInt(W_MIN, W_MAX, format("w[%d]", i+1));
  }
  inf.readEoln();
  for(int i = 0; i < M; i++) {
    u[i] = inf.readInt(1, N, format("u[%d]", i+1));
    inf.readSpace();
    v[i] = inf.readInt(1, N, format("v[%d]", i+1));
    inf.readEoln();
  }
  Q = inf.readInt(Q_MIN, Q_MAX, "Q");
  inf.readEoln();
  for(int i = 0; i < Q; i++) {
    x[i] = inf.readInt(1, N, format("x[%d]", i+1));
    inf.readEoln();
  }
  inf.readEof();
}

void check() {
  UnionFind uf(N);
  bool multi_edges = false;
  bool self_loop = false;
  set<pair<int, int>> edges;
  for(int i = 0; i < M; i++) {
    if(edges.count(minmax(u[i], v[i]))) multi_edges = true;
    if(u[i] == v[i]) self_loop = true;
    uf.unite(u[i]-1, v[i]-1);
    edges.insert(minmax(u[i], v[i]));
  }
  ensuref(!multi_edges, "Multiple edges");
  ensuref(!self_loop, "Self loop");
  ensuref(uf.size(0) == N, "Disconnected graph");
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
