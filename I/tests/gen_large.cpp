#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define CASE 10

const long long N_MAX = 100000;
const long long M_MAX = 100000;
const long long W_MIN = 100000;
const long long W_MAX = 1000000;

void start(int id) {
  ofstream fout(format("04_large_%02d.in", id).c_str());
  long long N = N_MAX;
  long long M = rnd.next(N-1, min(N*(N-1)/2, M_MAX));
  fout << N << " " << M << endl;
  for(int i = 0; i < N; i++) {
    if(i) fout << " ";
    fout << rnd.next(W_MIN, W_MAX);
  }
  fout << endl;
  set<pair<long long, long long>> st;
  for(int i = 0; i < N-1; i++) {
    long long v = i+2;
    long long u = rnd.next(1LL, v-1);
    fout << u << " " << v << endl;
    st.insert(minmax(u, v));
  }
  for(int i = N-1; i < M; i++) {
    long long u = rnd.next(1LL, N);
    long long v = rnd.next(1LL, N);
    while(u == v || st.count(minmax(u, v))) {
      u = rnd.next(1LL, N);
      v = rnd.next(1LL, N);
    }
    fout << u << " " << v << endl;
    st.insert(minmax(u, v));
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i < CASE; i++) {
    start(i);
  }
  return 0;
}
