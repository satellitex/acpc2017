#include "testlib.h"
#include <cmath>

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

const int NUM_OF_RANDOM_CASE = 10;


void random_gen( string name,int s = MAX_S, int n = MAX_N, double w = MAX_W, int l = MAX_L, int r = MAX_R, int z = MAX_Z ) {
  ofstream out( name );
  out << n << " " << m << endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if( j ) out << " ";
      out << rnd.next( MIN_H, MAX_H );
    }
    out << endl;
  }
  out.close();
}

int main(int argc, char *argv[])
{
  registerGen(argc, argv, 1);

  for(int t = 0; t < NUM_OF_RANDOM_CASE; t++ ){
    random_gen( format("50_random_%02d.in", t+1),
                rnd.next( MIN_N, MAX_N ), rnd.next( MIN_M, MAX_M ), rnd.next(MIN_H,MAX_H) );
  }
   
  return 0;
}
