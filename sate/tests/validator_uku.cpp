#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define PI 3.14159265358979323846

const int N_MIN = 1;
const int N_MAX = 1000;
const int S_MIN = 1;
const int S_MAX = 1000;
const double W_MIN = 0.0;
const double W_MAX = 2.0*PI;
const int L_MIN = 1;
const int L_MAX = 1000;
const int R_MAX = 10000;
const int X_MIN = -10000;
const int X_MAX = 10000;
const int Y_MIN = -10000;
const int Y_MAX = 10000;
const int V_MIN = 1;
const int V_MAX = 100;

int S, N, L, R;
int X, Y, V;
double W;

void input() {
  S = inf.readInt(S_MIN, S_MAX, "S");
  inf.readSpace();
  N = inf.readInt(N_MIN, N_MAX, "N");
  inf.readSpace();
  W = inf.readDouble(W_MIN, W_MAX, "W");
  inf.readSpace();
  L = inf.readInt(L_MIN, L_MAX, "L");
  inf.readSpace();
  R = inf.readInt(S+L, R_MAX, "R");
  inf.readEoln();
  X = inf.readInt(X_MIN, X_MAX, "X");
  inf.readSpace();
  Y = inf.readInt(Y_MIN, Y_MAX, "Y");
  inf.readSpace();
  V = inf.readInt(V_MIN, V_MAX, "V");
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
