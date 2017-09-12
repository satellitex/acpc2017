#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

#define MAX_N 100000

using ll = long long;

int main() {
  ll N, X, L;
  ll a[MAX_N+1], d[MAX_N+1];
  cin >> N >> X >> L;
  for(int i = 0; i < N; i++) cin >> a[i] >> d[i];

  auto f = [&](ll i, ll j, ll n) {
    if(i >= N) return 0ll;
    return (a[i]+j*d[i] + a[i]+(j+n-1)*d[i])*n/2;
  };
  ll asum[MAX_N+1];
  for(int i = 0; i < N; i++) asum[i+1] = asum[i]+f(i, 0, X);
  auto g = [&](ll i, ll j, ll n) {
    ll x = min(X-j, n), y = n-x, l = y/X, m = y%X;
    //if(n <= X-j) return f(i, j, x);
    if((N-i)*X < L) return 0ll;
    return f(i, j, x)+asum[i+1+l]-asum[i+1]+f(i+1+l, 0, m);
  };

  ll ans = 0;
  for(int i = 0; i < N; i++) {
    //if((N-i)*X < L) break;
    ll sum = g(i, max(0ll, X-L), L);
    if(i > 0) {
      ll lb = max(0ll, X-L), ub = X;
      while(lb+1 < ub) {
	int mb = (lb+ub)/2;
	if(g(i-1, mb, L)-g(i-1, mb-1, L) < 0) lb = mb;
	else ub = mb;
      }
      ll minimal = lb;
      auto findmax = [&](int lb, int ub) {
	while(lb+1 < ub) {
	  int mb = (lb+ub)/2;
	  if(g(i-1, mb, L)-g(i-1, mb-1, L) > 0) lb = mb;
	  else ub = mb;
	}
	return g(i-1, lb, L);
      };
      sum = max(sum, findmax(max(0ll, X-L), minimal));
      sum = max(sum, findmax(minimal, X));
    }
    ans = max(ans, sum);
  }
  cout << ans << endl;

  return 0;
}
