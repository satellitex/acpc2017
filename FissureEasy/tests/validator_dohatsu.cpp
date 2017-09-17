#include "testlib.h"
#include<bits/stdc++.h>

using namespace std;

const int MIN_N = 3;
const int MAX_N = 127;

int main(){
  registerValidation();
  int N = inf.readInt(MIN_N,MAX_N);
  assert( N%2 == 1 );
  
  inf.readEoln();

  for(int i=0;i<N;i++){
    string s = inf.readToken(format("[a-z]{%d, %d}", N, N), "S");
    for(int j=0;j<N;j++) assert( s[j] == 'o' || s[j]=='x');
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
