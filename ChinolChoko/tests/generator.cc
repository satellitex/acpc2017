#include <bits/stdc++.h>
#include <random>
#include "../../Cluster/tests/testlib.h"
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> PP;
int N=200,M=15;
int main(int argc, char* argv[]) {
  registerGen(argc, argv);
  for(int t=0; t<30; t++) {
    ofstream ofs(format("03_random_%02d.in",t).c_str());
    int n=rnd.next(2,N),m=rnd.next(1,M);
    ofs << n << " " << m << endl;
    for(int i=0; i<n; i++) {
      for(int j=0; j<4; j++) {
        if(j) ofs << " ";
        ofs << rnd.next(0,1000);
      }
      ofs << endl;
    }
    for(int i=0; i<m; i++) ofs << rnd.next(0,1000) << " " << rnd.next(0,1000) << endl;
  }
  return 0;
}
