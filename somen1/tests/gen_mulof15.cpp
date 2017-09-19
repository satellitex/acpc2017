#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i*15 < 360; i++) {
    ofstream fout(format("01_corner_%02d.in", i).c_str());
    fout << i*15 << endl;
  }
  return 0;
}
