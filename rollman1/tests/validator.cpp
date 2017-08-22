#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const int MIN_N = 1;
const int MAX_N = 1e5;
const int MIN_A = 0;
const int MAX_A = 1e9;

int N;
int a[MAX_N];

void input() {
  N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readEoln();
  for(int i = 0; i < N; i++) {
    a[i] = inf.readInt(MIN_A, MAX_A, format("a[%d]", i+1));
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
