#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 10

const int MIN_N = 50000;
const int MAX_N = 100000;
const int MIN_X = 500000;
const int MAX_X = 1000000;

void start(int id) {
  ofstream out(format("02_large_%02d.in", id).c_str());
  int N = rnd.next(1, MAX_N);
  out << N << endl;
  for(int i = 0; i < N; i++) {
    if(i) out << " ";
    int x = rnd.next(MIN_N, MAX_X);
    if(x == MIN_X) x = 0;
    out << x;
  }
  out << endl;
  for(int v = 2; v <= N; v++) {
    int u = rnd.next(1, v-1);
    out << u << " " << v << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
