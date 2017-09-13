#include "testlib.h"

using namespace std;

const int N_MIN = 2;
const int N_MAX = 200000;
const int Q_MIN = 2;
const int Q_MAX = 200000;
const int A_MIN = 1;
const int A_MAX = 1000000000;
const int X_MIN = 1;
const int X_MAX = 6;

int main(){
  registerValidation();
  
  int N = inf.readInt(N_MIN, N_MAX);
  inf.readEoln();

  for(int t=0;t<2;t++){
    for (int i = 0; i < N; i++) {
      if(i)inf.readSpace();
      int a=inf.readInt(A_MIN,A_MAX);
    }
    inf.readEoln();
  }

  int Q = inf.readInt(Q_MIN,Q_MAX);
  inf.readEoln();
  for(int i=0;i<Q;i++){
    int x,y,z;
    x=inf.readInt(X_MIN,X_MAX);
    inf.readSpace();
      
    if(x==1||x==2){
      y=inf.readInt(1,N);
      inf.readSpace();
      z=inf.readInt(A_MIN,A_MAX);
      inf.readEoln();
    }
      
    if(x==3||x==4){
      y=inf.readInt(1,N);
      inf.readSpace();
      z=inf.readInt(1,N);
      inf.readEoln();
      assert(y<=z);
    }

    if(x==5||x==6){
      y=inf.readInt(-1,-1);
      inf.readSpace();
      z=inf.readInt(-1,-1);
      inf.readEoln();
    }
      
  }
    
  inf.readEof();

    
  return 0;
}
