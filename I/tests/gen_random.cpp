#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define CASE 20

const long long N_MIN = 1;
const long long N_MAX = 100000;
const long long M_MAX = 100000;
const long long W_MIN = 1;
const long long W_MAX = 1000000;

void start(int id) {
  ofstream fout(format("03_random_%02d.in", id).c_str());
  long long N = rnd.next(N_MIN, N_MAX);
  long long M = rnd.next(N-1, min(M_MAX, N*(N-1)/2));
  fout << N << " " << M << endl;
  for(int i = 0; i < N; i++) {
    if(i) fout << " ";
    fout << rnd.next(W_MIN, W_MAX);
  }
  fout << endl;
  set<pair<long long, long long>> st;
  vector<long long> u(M), v(M);
  for(int i = 0; i < N-1; i++) {
    v[i] = i+2;
    u[i] = rnd.next(1LL, v[i]-1);
    st.insert(minmax(u[i], v[i]));
  }
  for(int i = N-1; i < M; i++) {
    u[i] = rnd.next(1LL, N);
    v[i] = rnd.next(1LL, N);
    while(u[i] == v[i] || st.count(minmax(u[i], v[i]))) {
      u[i] = rnd.next(1LL, N);
      v[i] = rnd.next(1LL, N);
    }
    st.insert(minmax(u[i], v[i]));
  }
  vector<int> vid(N);
  iota(vid.begin(), vid.end(), 1);
  random_device seed_gen;
  mt19937 engine(seed_gen());
  shuffle(vid.begin(), vid.end(), engine);
  for(int i = 0; i < M; i++) {
    fout << vid[u[i]-1] << " " << vid[v[i]-1] << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i < CASE; i++) {
    start(i);
  }
  return 0;
}
