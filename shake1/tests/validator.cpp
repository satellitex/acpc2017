#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const long long MIN_N = 1LL;
const long long MAX_N = 1e18*1LL;

long long N;

void input() {
  N = inf.readLong(MIN_N, MAX_N, "N");
  inf.readEoln();
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
