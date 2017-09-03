#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const int MIN_N = 1;
const int MAX_N = 5000;

int N;
int p[MAX_N];

void input() {
  N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readEoln();
  for(int i = 0; i < N; i++) {
    p[i] = inf.readInt(0, i, format("p[%d]", i+1));
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
