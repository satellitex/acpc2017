#include <iostream>
#include "testlib.h"

using namespace std;

#define CASE_NUM 10

const long long MIN_N = 1LL;
const long long MAX_N = 1e18*1LL;

void start(int id) {
  ofstream out(format("20_random_%02d.in", id).c_str());
  long long N = rnd.next(MIN_N, MAX_N);
  out << N << endl;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
