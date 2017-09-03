#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 20

const int MAX_N = 5000;

void start(int id) {
  ofstream out(format("20_random_%02d.in", id).c_str());
  int N = rnd.next(1, MAX_N);
  out << N << endl;
  for(int i = 0; i < N; i++) {
    out << rnd.next(0, i) << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
