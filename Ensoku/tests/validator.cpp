#include <iostream>
#include <vector>
#include "testlib.h"

using namespace std;

const int MAX_A = 10000;
const int MAX_B = 1000;
const int MAX_N = 10;
const int MAX_K = 100;
const int MAX_a = 1000;
const int MAX_b = 1000;
const int MAX_c = 1000;
const int MAX_d = 10000;

const int MIN_A = 1;
const int MIN_B = 1;
const int MIN_N = 1;
const int MIN_K = 1;
const int MIN_a = 1;
const int MIN_b = 1;
const int MIN_c = 1;
const int MIN_d = 0;

void input() {
  int N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readSpace();
  int A = inf.readInt(MIN_A, MAX_A, "A");
  inf.readSpace();
  int B = inf.readInt(MIN_B, MAX_B, "B");
  inf.readEoln();
  ensuref(B<=A,"A must be lather than B or equal B");
  
  for(int i = 0; i < N; i++) {
    int K = inf.readInt(MIN_K, MAX_K, "K");
    inf.readEoln();
    for(int j=0;j<K;j++) {
      int a = inf.readInt(MIN_a, MAX_a, "a");
      inf.readSpace();
      int b = inf.readInt(MIN_b, MAX_b, "b");
      inf.readSpace();
      int c = inf.readInt(MIN_c, MAX_c, "c");
      inf.readEoln();
    }
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(j) inf.readSpace();
      int d = inf.readInt(MIN_d, MAX_d, "d");
      ensuref(i!=j || d == 0,"if i == j, d must be 0");
    }
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
