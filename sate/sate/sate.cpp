#include<bits/stdc++.h>
using namespace std;
typedef complex<double> P;

double S,N,W,R,L,X,Y,V;
double getCod(double rad){
  return rad * 180.0 / M_PI;
}

bool check(double t){
  // 最も近づく点を三分三択？
}

int main(){
  cin >> S >> N >> W >> L >> R;
  cin >> X >> Y >> V;

  S += L;
  L += L;

  P v = P(X,Y);
  double at = arg(v);
  if( at < 0 )
    at = -at;
  else
    at = 2*M_PI - at;
  cout << at << ": " << getCod(at) << endl;

  double rmd = at/W;
  double x = abs(X,Y) - R - L;

  if( x > 0 ){
    double st = rmd - x/V;
    double ed = rmd + 2*M_PI/N/W;
    while( st <= ed ){
      double h = (st+ed)/2.0;

    }
  }


}