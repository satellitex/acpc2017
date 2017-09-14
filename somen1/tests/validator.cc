#include "testlib.h"

using namespace std;
const int X_MIN = 0;
const int X_MAX = 359;

int X;
void input(){
  X = inf.readInt(X_MIN,X_MAX,"X");
  inf.readEoln();
  inf.readEof();
}

int main(){
  registerValidation();

  input();

  return 0;
}
