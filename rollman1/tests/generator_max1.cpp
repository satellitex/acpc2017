#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 1

const int MAX_N = 1e5;
const int MAX_A = 1e9;

void start(int id) {
  ofstream out(format("90_max1_%02d.in", id).c_str());
  int N = MAX_N;
  out << N << endl;
  for(int i = 0; i < N; i++) {
    out << MAX_A - i << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
