#include <iostream>
#include <vector>
#include "testlib.h"

typedef long long ll;

using namespace std;

const int MIN_N = 1;
const int MAX_N = 1e5;
const int MIN_X = 1;
const int MAX_X = 1e5;
const int MIN_L = 1;

const int MIN_a = 0;
const int MAX_a = 1e5;
const int MIN_d = 1;
const int MAX_d = 1e3;

int N, X, L;
int a[MAX_N];
int d[MAX_N];

void input() {
  N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readSpace();
  X = inf.readInt(MIN_X, MAX_X, "X");
  inf.readSpace();
  L = inf.readLong(MIN_L, (ll)N*X, "L");
  inf.readEoln();
  for(int i = 0; i < N; i++) {
    a[i] = inf.readInt(MIN_a, MAX_a, format("a[%d]", i+1));
    inf.readSpace();
    d[i] = inf.readInt(MIN_d, MAX_d, format("d[%d]", i+1));
    inf.readEoln();
  }
  inf.readEof();
}

void check() {
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
