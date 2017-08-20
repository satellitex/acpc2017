#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 1

const int MAX_N = 10;
const int MAX_X = 10;

void start(int id) {
  ofstream out(format("00_small_%02d.in", id).c_str());
  int N = MAX_N;//rnd.next(1, MAX_N);
  out << N << endl;
  for(int i = 0; i < N; i++) {
    if(i) out << " ";
    out << rnd.next(0, MAX_X);
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
