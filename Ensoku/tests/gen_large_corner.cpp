#include <iostream>
#include "testlib.h"
using namespace std;
#define CASE_NUM 3

const int MAX_A = 10000;
const int MAX_B = 1000;
const int MAX_N = 10;
const int MAX_K = 100;
const int MAX_a = 3;
const int MAX_b = 1000;
const int MAX_c = 1000;
const int MAX_d = 2000;


const int MIN_A = 10000;
const int MIN_B = 1000;
const int MIN_N = 10;
const int MIN_K = 100;
const int MIN_a = 1;
const int MIN_b = 1;
const int MIN_c = 950;
const int MIN_d = 0;

void start(int id) {
  ofstream out(format("04_large_corner_%02d.in", id).c_str());
  int N = rnd.next(MIN_N, MAX_N);
  int A = rnd.next(MIN_A, MAX_A);
  int B = rnd.next(MIN_B, min(MAX_B,A));
  out<<N<<" "<<A<<" "<<B<<endl;

  for(int i = 0; i < N; i++) {
    int K = rnd.next(MIN_K,MAX_K);
    out << K << endl;
    for(int j=0;j<K;j++) {
      int a = rnd.next(MIN_a,MAX_a);
      int b = rnd.next(MIN_b,MAX_b);
      int c = rnd.next(MIN_c,MAX_c);
      out<<a<<" "<<b<<" "<<c<<endl;
    }
  }

  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++){
      if( j ) out << " ";
      int d = rnd.next(MIN_d,MAX_d);
      if (i == j) d = 0;
      out << d;
    }
    out << endl;
  }
  
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) start(t);
  return 0;
}
