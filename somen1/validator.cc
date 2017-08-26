#include "testlib.h"

using namespace std;
const int Theta_MIN = 0;
const int Theta_MAX = 360;

int Theta;
void input(){
  Theta = inf.readInt(Theta_MIN,Theta_MAX,"Theta");
  inf.readEoln();
}

int main(){
  registerValidation();

  input();

  return 0;
}
