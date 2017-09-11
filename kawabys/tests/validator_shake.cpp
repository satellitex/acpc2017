#include<iostream>
#include"testlib.h"
using namespace std;
#define MIN_N 1
#define MAX_N 100000
#define MIN_X 1
#define MAX_X 100000
#define MIN_L 1
#define MIN_a 0
#define MAX_a 100000
#define MIN_d 1
#define MAX_d 1000

int N,X,L;
int a[MAX_N];
int d[MAX_N];

void input(){
  N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readSpace();
  X = inf.readInt(MIN_X, MAX_X, "X");
  inf.readSpace();
  L = inf.readLong(MIN_L, (long long)N*X, "L");
  inf.readEoln();
  for(int i=0;i<N;i++){
    a[i] = inf.readInt(MIN_a, MAX_a, format("a[%d]",i+1));
    inf.readSpace();
    d[i] = inf.readInt(MIN_d, MAX_d, format("d[%d]",i+1));
    inf.readEoln();
  }
  inf.readEof();
}

int main(){
  registerValidation();
  input();
  return 0;
}
