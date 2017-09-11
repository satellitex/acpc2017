#include <iostream>
#include <string>
#include <cassert>
#include "testlib.h"
using namespace std;
#define min_n 1
#define max_n 1000
#define min_m 1
#define max_m 30
int main(){
  registerValidation();
  
  int n,m;
  
  n=inf.readInt(min_n,max_n);
  inf.readSpace();
  m=inf.readInt(min_m,max_m);
  inf.readEoln();
  
  for(int i=0;i<n;i++){
    string s=inf.readString();
    if((int)s.size()!=m) assert(1);
    for(int j=0;j<(int)s.size();j++) if(!('a'<=s[j]&&s[j]<='z')) assert(1);
  }
  inf.readEof();
  return 0;

}
