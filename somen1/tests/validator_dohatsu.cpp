#include "testlib.h"
using namespace std;
const int N_MIN = 1;
const int N_MAX = 1000;
const int TI_MIN = 0;
const int TI_MAX = 359;

int main(){
  registerValidation();
  int N = inf.readInt(N_MIN, N_MAX);
  inf.readEoln();
  
  for(int i=0;i<N;i++){
    int ti=inf.readInt(TI_MIN,TI_MAX);
    inf.readEoln();
  }
    
  inf.readEof();

    
  return 0;
}
