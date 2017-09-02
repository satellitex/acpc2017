#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define CASE_NUM 10

const int N_MIN = 2;
const int N_MAX = 10;
const int C_MIN = 1;
const int C_MAX = 100;
const int Q_MIN = 1;
const int Q_MAX = 10;

void start(int id) {
  ofstream fout(format("01_small_%02d.in", id).c_str());
  int N = rnd.next(N_MIN, N_MAX);
  int M = rnd.next(N-1, N*(N-1)/2);
  int T = rnd.next(1, N);
  fout << N << " " << M << " " << T << endl;
  vector<int> a(M), b(M), c(M);
  set<pair<int, int>> ste;
  set<int> stc;
  for(int i = 0; i < N-1; i++) {
    a[i] = i+1;
    b[i] = rnd.next(0, i);
    c[i] = rnd.next(C_MIN, C_MAX);
    while(stc.count(c[i])) c[i] = rnd.next(C_MIN, C_MAX);
    ste.emplace(a[i], b[i]);
    ste.emplace(b[i], a[i]);
    stc.insert(c[i]);
  }
  for(int i = N-1; i < M; i++) {
    a[i] = rnd.next(0, N-1);
    b[i] = rnd.next(0, N-1);
    while(a[i] == b[i] || ste.count(make_pair(a[i], b[i]))) b[i] = rnd.next(0, N-1);
    c[i] = rnd.next(C_MIN, C_MAX);
    while(stc.count(c[i])) c[i] = rnd.next(C_MIN, C_MAX);
    ste.emplace(a[i], b[i]);
    ste.emplace(b[i], a[i]);
    stc.insert(c[i]);
  }
  vector<int> vid(N);
  iota(vid.begin(), vid.end(), 1);
  random_device seed_gen;
  mt19937 engine(seed_gen());
  shuffle(vid.begin(), vid.end(), engine);
  for(int i = 0; i < M; i++) {
    fout << vid[a[i]] << " " << vid[b[i]] << " " << c[i] << endl;
  }
  int Q = rnd.next(Q_MIN, Q_MAX);
  fout << Q << endl;
  for(int i = 0; i < Q; i++) {
    int u = rnd.next(1, N);
    int v = rnd.next(1, N);
    while(u == v) v = rnd.next(1, N);
    fout << u << " " << v << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
