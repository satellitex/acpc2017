#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const int MAX_n = 1000;
const int MAX_m = 12;
const int MAX_d = 30;
const int MAX_v = 360;
const int MAX_s = 360;

int n;
int m[MAX_n];
int d[MAX_n];
int v[MAX_n];
int s[MAX_s];

void input() {
  n = inf.readInt(1, MAX_n, "n");
  inf.readEoln();
  for(int i = 0; i < n; i++) {
    m[i] = inf.readInt(1, MAX_m, format("m[%d]", i+1));
    inf.readSpace();
    d[i] = inf.readInt(1, MAX_d, format("d[%d]", i+1));
    inf.readSpace();
    v[i] = inf.readInt(1, MAX_v, format("v[%d]", i+1));
    inf.readSpace();
    s[i] = inf.readInt(1, MAX_s, format("s[%d]", i+1));
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
