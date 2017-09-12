#include <bits/stdc++.h>
#include "../../I/tests/testlib.h"

using namespace std;

const int MIN_N = 2;
const int MAX_N = 200;
const int MIN_M = 1;
const int MAX_M = 15;
const int MIN_Z = 0;
const int MAX_Z = 1000;

void input(){
  int n = inf.readInt(MIN_N,MAX_N,"N");
  inf.readSpace();
  int m = inf.readInt(MIN_M,MAX_M,"M");
  inf.readEoln();
  for(int i=0;i<n;i++){
    int a = inf.readInt(MIN_Z,MAX_Z,"a_"+to_string(i));
    inf.readSpace();
    int b = inf.readInt(MIN_Z,MAX_Z,"b_"+to_string(i));
    inf.readSpace();
    int c = inf.readInt(MIN_Z,MAX_Z,"c_"+to_string(i));
    inf.readSpace();
    int d = inf.readInt(MIN_Z,MAX_Z,"d_"+to_string(i));
    inf.readEoln();
  }
  for(int i=0;i<m;i++){
    int x = inf.readInt(MIN_Z,MAX_Z,"x_"+to_string(i));
    inf.readSpace();
    int y = inf.readInt(MIN_Z,MAX_Z,"y_"+to_string(i));
    inf.readEoln();
  }
  inf.readEof();
}

int main(){
  registerValidation();
  input();
}