#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  for(int i = 0; i*31 < 360; i++) {
    ofstream fout(format("02_corner_%02d.in", i).c_str());
    fout << i*31 << endl;
  }
  return 0;
}
