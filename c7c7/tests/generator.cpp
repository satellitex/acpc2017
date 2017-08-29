#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "testlib.h"

using namespace std;

#define CASE_NUM 20

const int MAX_M = 25 ;
const int N =1000 ;
const int seed =1000000007;

vector<string>v;
void start(int id) {
  ofstream out(format("50_random_%02d.in", id).c_str());
  int M = rnd.next(1, MAX_M);
  out << N << " " << M << endl;
  for(int i = 0; i < N; i++) {

    if(i%10==3){
      int point=rnd.next(0,seed)%(int)v.size();
      out<<v[point]<<endl;
      //v.erase(v.begin()+point);
    }

    else {
      string t="";
      for(int j = 0; j < M ; j++){
        char c=rnd.next(0, MAX_M)+'a';
         t+=c;
       }
       reverse(t.begin(),t.end());
       v.push_back(t);
       out<<t<<endl;
     }
  }
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int t = 0; t < CASE_NUM; ++t) {
    v.clear();
    start(t);
  }
  return 0;
}