#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

using namespace std;
const int MIN_N = 1;
const int MAX_N = 1000;
const int MIN_S = 1;
const int MAX_S = 1000;
const double MIN_W = 0.0;
const double MAX_W = 2*M_PI;
const int MIN_L = 1;
const int MAX_L = 1000;
const int MAX_R = 10000;
const int MIN_Z = -10000;
const int MAX_Z = 10000;
const int MIN_V = 1;
const int MAX_V = 100;

const int NUM_OF_RANDOM_CASE = 10;


void random_gen( string name,int s = MAX_S, int n = MAX_N, double w = MAX_W, int l = MAX_L, int r = MAX_R, int x = MAX_Z, int y = MAX_Z, int v = MAX_V ) {
  ofstream out( name );
  out << s << " " << n << " " << w << " " << l << " " << r << " " << endl;
  out << x << " " << y << " " << v << endl;
  out.close();
}

int main(int argc, char *argv[])
{
  registerValidation();
  int S = inf.readInt( MIN_S, MAX_S, "S" );
  inf.readSpace();
  int N = inf.readInt( MIN_N, MAX_N, "N" );
  inf.readSpace();

  double W = inf.readDouble( MIN_W, MAX_W, "W" );
  inf.readSpace();

  int L = inf.readInt( MIN_L, MAX_L, "L" );
  inf.readSpace();
  int R = inf.readInt( S+L, MAX_R, "R" );
  inf.readSpace();
  inf.readEoln();

  int X = inf.readInt( MIN_Z, MAX_Z, "Z" );
  int Y = inf.readInt( MIN_Z, MAX_Z, "Z" );
  int V = inf.readInt( MIN_V, MAX_V, "V" );
  inf.readEof();

  return 0;
}
