#include "testlib.h"

using namespace std;
const int N_MIN = 1;
const int N_MAX = 1000;
const int X_MIN = 0;
const int X_MAX = 360;

int N;
int X[N_MAX];
void input(){
  N = inf.readInt(N_MIN,N_MAX,"N");
  inf.readEoln();
  for(int i=0;i<N;i++){
    X[i] = inf.readInt(X_MIN,X_MAX,format("X[%d]",i));
    inf.readEoln();
  }
  inf.readEof();
}

int main(){
  registerValidation();

  input();

  return 0;
}
