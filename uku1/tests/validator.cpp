#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const int MIN_N = 1;
const int MAX_N = 100000;
const int MIN_X = 0;
const int MAX_X = 1000000;

int N;
int x[MAX_N];
int a[MAX_N], b[MAX_N];

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
  N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readEoln();
  for(int i = 0; i < N; i++) {
    if(i) inf.readSpace();
    x[i] = inf.readInt(MIN_X, MAX_X, format("x[%d]", i+1));
  }
  inf.readEoln();
  for(int i = 0; i < N-1; i++) {
    a[i] = inf.readInt(1, N, format("a[%d]", i+1));
    inf.readSpace();
    b[i] = inf.readInt(1, N, format("b[%d]", i+1));
    inf.readEoln();
  }
  inf.readEof();
}

void check() {
  UnionFind uf(N);
  for(int i = 0; i < N-1; i++) {
    uf.unite(a[i]-1, b[i]-1);
  }
  ensuref(uf.size(0) == N, "Disconnected graph");
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
