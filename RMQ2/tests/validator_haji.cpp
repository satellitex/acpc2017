#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const int MAX_N = 2 * (1e5);
const int MAX_Q = 2 * (1e5);
const int MAX_a = 1e9;
const int MAX_b = 1e9;
const int MAX_x = 6;

const int MIN_N = 2;
const int MIN_Q = 2;
const int MIN_a = 1;
const int MIN_b = 1;
const int MIN_x = 1;


void input() {
  int N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readEoln();

  for(int i=0;i<N;i++) {
    if(i)inf.readSpace();
    inf.readInt(MIN_a, MAX_a, "a");
  }
  inf.readEoln();
  
  for(int i=0;i<N;i++) {
    if(i)inf.readSpace();
    inf.readInt(MIN_b, MAX_b, "b");
  }
  inf.readEoln();
  
  int Q = inf.readInt(MIN_Q, MAX_Q, "Q");
  inf.readEoln();
  for(int i=0;i<Q;i++) {
    int x = inf.readInt(MIN_x, MAX_x, "x");
    inf.readSpace();

    if(1<=x&&x<=4) inf.readInt(1, N, "y");
    if(5<=x&&x<=6) inf.readInt(-1, -1, "y");
    inf.readSpace();

    if(1<=x&&x<=2) inf.readInt(1, 1e9, "z");
    if(3<=x&&x<=4) inf.readInt(1, N, "z");
    if(5<=x&&x<=6) inf.readInt(-1, -1, "z");
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
