#include <iostream>
#include "testlib.h"
using namespace std;
#define CASE_NUM 1

const int MAX_A = 1000;
const int MAX_B = 1000;
const int MAX_N = 14;
const int MAX_K = 300;
const int MAX_a = 1;
const int MAX_b = 1000;
const int MAX_c = 1000;
const int MAX_d = 0;

const int MIN_A = 1000;
const int MIN_B = 1000;
const int MIN_N = 14;
const int MIN_K = 300;
const int MIN_a = 1;
const int MIN_b = 1;
const int MIN_c = 1000;
const int MIN_d = 0;

void start(int id) {
  ofstream out(format("05_O2_killer_%02d.in", id).c_str());
  int N = rnd.next(MIN_N, MAX_N);
  int A = rnd.next(MIN_A, MAX_A);
  int B = rnd.next(MIN_B, min(MAX_B,A));
  out<<N<<" "<<A<<" "<<B<<endl;

  int K = rnd.next(MIN_K,MAX_K);
  int a[K],b[K],c[K];
  for(int j=0;j<K;j++) {
    a[j] = rnd.next(MIN_a,MAX_a);
    b[j] = rnd.next(MIN_b,MAX_b);
    c[j] = rnd.next(MIN_c,MAX_c);
  }    
  
  for(int i = 0; i < N; i++) {
    out << K << endl;
    for(int j = 0; j < K ;j++) out<<a[j]<<" "<<b[j]<<" "<<c[j]<<endl;
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
