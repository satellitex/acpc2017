#include <iostream>
#include "testlib.h"

using namespace std;

const int MIN_N = 1;
const int MAX_N = 100;
const int MIN_M = 1;
const int MAX_M = 100;
const int MIN_L = 1;
const int MIN_B = 1;
const int MAX_B = 1000;
const int MAX_P = 100;

int N, M;
int l[MAX_M], b[MAX_M];
int p[MAX_N][MAX_M];

void input() {
  N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readSpace();
  M = inf.readInt(MIN_M, MAX_M, "M");
  inf.readEoln();
  for(int i = 0; i < M; i++) {
    if(i) inf.readSpace();
    l[i] = inf.readInt(MIN_L, N, format("l[%d]", i+1));
  }
  inf.readEoln();
  for(int i = 0; i < M; i++) {
    if(i) inf.readSpace();
    b[i] = inf.readInt(MIN_B, MAX_B, format("b[%d]", i+1));
  }
  inf.readEoln();
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      if(j) inf.readSpace();
      p[i][j] = inf.readInt(-1, MAX_P, format("p[%d][%d]", i, j));
    }
    inf.readEoln();
  }
  inf.readEof();
}

void check() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      ensuref(p[i][j] != 0, "exist p == 0");
    }
  }
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
