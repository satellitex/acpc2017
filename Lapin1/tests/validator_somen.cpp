#include "testlib.h"
using namespace std;
const int N_MIN = 1;
const int N_MAX = 100;
const int M_MIN = 1;
const int M_MAX = 12;
const int D_MIN = 1;
const int D_MAX = 30;
const int V_MIN = 1;
const int V_MAX = 360;
const int S_MIN = 1;
const int S_MAX = 360;
int N;
int M[N_MAX],D[N_MAX],V[N_MAX],S[N_MAX];
void input(){
  N = inf.readInt(N_MIN,N_MAX,"N");
  inf.readEoln();
  for(int i=0;i<N;i++){
    M[i]=inf.readInt(M_MIN,M_MAX,format("M[i]",i));
    inf.readSpace();
    D[i]=inf.readInt(D_MIN,D_MAX,format("D[i]",i));
    inf.readSpace();
    V[i]=inf.readInt(V_MIN,V_MAX,format("V[i]",i));
    inf.readSpace();
    S[i]=inf.readInt(S_MIN,S_MAX,format("S[i]",i));
    inf.readEoln();
  }
  inf.readEof();
}
int main(){
  registerValidation();
  input();
  return 0;
}
