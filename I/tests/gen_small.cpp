#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define CASE 1000

const int N_MIN = 1;
const int N_MAX = 30;

void start(int id) {
  ofstream fout(format("01_small_%02d.in", id).c_str());
  int N = rnd.next(N_MIN, N_MAX);
  int M = rnd.next(N-1, N*(N-1)/2);
  fout << N << " " << M << endl;
  for(int i = 0; i < N; i++) {
    if(i) fout << " ";
    fout << i+1;
  }
  fout << endl;
  set<pair<int, int>> st;
  for(int i = 0; i < N-1; i++) {
    int v = i+2;
    int u = rnd.next(1, v-1);
    fout << u << " " << v << endl;
    st.insert(minmax(u, v));
  }
  for(int i = N-1; i < M; i++) {
    int u = rnd.next(1, N);
    int v = rnd.next(1, N);
    while(u == v || st.count(minmax(u, v))) {
      u = rnd.next(1, N);
      v = rnd.next(1, N);
    }
    fout << u << " " << v << endl;
    st.insert(minmax(u, v));
  }
  int Q = N;
  fout << Q << endl;
  for(int i = 0; i < Q; i++) {
    fout << i+1 << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i < CASE; i++) {
    start(i);
  }
  return 0;
}
