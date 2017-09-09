#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int N=2048;
int main() {
  registerValidation();
  int n=inf.readInt(2, N, "n");
  inf.readEoln();
  ensure(n%2==1);
  for(int i=0; i<n; i++) {
    string s=inf.readToken("[ox]*");
    ensure(s.size()==n);
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
