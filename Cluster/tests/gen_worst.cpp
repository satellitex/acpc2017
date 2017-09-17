#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define CASE 3

const long long N_MAX = 100000;
const long long M_MAX = 100000;
const long long W_MIN = 100000;
const long long W_MAX = 1000000;

void start(int id) {
  ofstream fout(format("20_worst_%02d.in", id).c_str());
  long long N = N_MAX;
  long long M = N;
  fout << N << " " << M << endl;
  for(int i = 0; i < N; i++) {
    if(i) fout << " ";
    fout << rnd.next(W_MIN, W_MAX);
  }
  fout << endl;
  set<pair<long long, long long>> st;
  vector<long long> u(M), v(M);
  for(int i = 0; i < 10; i++) {
    u[i] = i;
    v[i] = (i+1)%10;
    assert(st.count(minmax(u[i], v[i])) == 0);
    st.insert(minmax(u[i], v[i]));
  }
  for(int i = 10; i < M; i++) {
    u[i] = i%10;
    v[i] = i;
    assert(st.count(minmax(u[i], v[i])) == 0);
    st.insert(minmax(u[i], v[i]));
  }
  vector<int> vid(N);
  iota(vid.begin(), vid.end(), 1);
  random_device seed_gen;
  mt19937 engine(seed_gen());
  shuffle(vid.begin(), vid.end(), engine);
  for(int i = 0; i < M; i++) {
    fout << vid[u[i]] << " " << vid[v[i]] << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i < CASE; i++) start(i);
  return 0;
}
