#include <bits/stdc++.h>
#include <random>
#include "../../uku1/tests/testlib.h"
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> PP;
int N=1000;
int main(int argc, char* argv[]) {
  registerGen(argc, argv);
  for(int t=0; t<30; t++) {
    ofstream ofs(format("03_random_%02d.in",t).c_str());
    int n=rnd.next(1,N);
    int m=rnd.next(0,n*(n-1));
    vector<PP> v;
    for(int i=0; i<n; i++) {
      for(int j=i+1; j<n; j++) {
        for(int k=0; k<2; k++) v.push_back(PP(P(i,j),k));
      }
    }
    shuffle(v.begin(),v.end(),default_random_engine((unsigned)time(NULL)));
    int a[n],b[n];
    for(int i=0; i<n; i++) a[i]=rnd.next(0,1000000000);
    for(int i=0; i<n; i++) b[i]=rnd.next(-a[i],1000000000);
    for(int i=0; i<n; i++) {
      if(i) ofs << " ";
      ofs << a[i];
    }
    ofs << endl;
    for(int i=0; i<n; i++) {
      if(i) ofs << " ";
      ofs << b[i];
    }
    ofs << endl;
    for(int i=0; i<m; i++) ofs << v[i].first.first << " " << v[i].first.second << " " << v[i].second << " " << rnd.next(0,2000000000) << endl;
  }
  return 0;
}
