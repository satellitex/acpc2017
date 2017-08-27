#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 100

const int MIN_N = 1;
const int MAX_N = 500;
const int MIN_M = 1;
const int MAX_M = 500;
const int MIN_L = 1;
const int MIN_B = 1;
const int MAX_B = 1000;
const int MAX_P = 100;

void start(int id) {
  ofstream out(format("02_large_%02d.in", id).c_str());
  int N = MAX_N;
  int M = MAX_N;
  out << N << " " << M << endl;
  for(int i = 0; i < M; i++) {
    if(i) out << " ";
    out << rnd.next(MIN_L, N);
  }
  out << endl;
  for(int i = 0; i < M; i++) {
    if(i) out << " ";
    out << rnd.next(MIN_B, MAX_B);
  }
  out << endl;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      if(j) out << " ";
      int p = rnd.next(1, MAX_P);
      if(p == 0) out << -1;
      else out << p;
    }
    out << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
