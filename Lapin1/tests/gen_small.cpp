#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 5

const int MAX_n = 10;
const int MAX_m = 12;
const int MAX_d = 30;
const int MAX_v = 360;
const int MAX_s = 360;

void start(int id) {
  ofstream out(format("neet_random_%02d.in", id).c_str());
  int n = rnd.next(1, MAX_n);
  out << n << endl;
  for(int i = 0; i < n; i++) {
    out << rnd.next(1, MAX_m) <<" "<< rnd.next(1, MAX_d) <<" "<< rnd.next(1, MAX_v) <<" "<< rnd.next(1, MAX_s) <<endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
