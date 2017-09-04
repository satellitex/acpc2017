#include <iostream>
#include "testlib.h"

using namespace std;

typedef long long ll;

#define CASE_NUM 20
const int MIN_N = 1;
const int MAX_N = 1e5;
const int MIN_X = 1;
const int MAX_X = 1e5;

const int MIN_a = 0;
const int MAX_a = 1e5;
const int MIN_d = 1;
const int MAX_d = 1e3;

const ll MIN_L = 1;

void start(int id) {
  ofstream out(format("50_random_%02d.in", id).c_str());
  int N = rnd.next(MIN_N, MAX_N);
  int X = rnd.next(MIN_X, MAX_X);
  ll L = rnd.next(MIN_L, (ll)N*X);
  out << N << " " << X << " " << L << endl;
  for(int i = 0; i < N; i++){
    int a = rnd.next(MIN_a, MAX_a);
    int d = rnd.next(MIN_d, MAX_d);
    out << a << " " << d << endl;
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    start(t);
  }
  return 0;
}
