#include <bits/stdc++.h>
#include "../../I/tests/testlib.h"
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll N=200,M=15;
int main() {
  registerValidation();
  int n=inf.readInt(2, N, "n");
  inf.readSpace();
  int m=inf.readInt(1, M, "m");
  inf.readEoln();
  for(int i=0; i<n; i++) {
    int a=inf.readInt(0, 1000, "a");
    inf.readSpace();
    int b=inf.readInt(0, 1000, "b");
    inf.readSpace();
    int c=inf.readInt(0, 1000, "c");
    inf.readSpace();
    int d=inf.readInt(0, 1000, "d");
    inf.readEoln();
  }
  for(int i=0; i<m; i++) {
    int x=inf.readInt(0, 1000, "x");
    inf.readSpace();
    int y=inf.readInt(0, 1000, "y");
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
