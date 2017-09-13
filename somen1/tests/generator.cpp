#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int T_MIN = 0;
const int T_MAX = 359;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i < 12; i++) {
    ofstream fout(format("03_random_%02d.in", i).c_str());
    fout << rnd.next(T_MIN, T_MAX) << endl;
  }
  return 0;
}
