#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 100000

using ll = long long;

int main() {
  ll N, X, L;
  ll a[MAX_N], d[MAX_N];
  cin >> N >> X >> L;
  for(int i = 0; i < N; i++) cin >> a[i] >> d[i];
  auto Sum1 = [&](int i, int y, int x) {return (a[i]+y*d[i]+a[i]+(y+x-1)*d[i])*x/2;};
  if(L < 2*X) {
    ll ans = 0;
    for(int i = 0; i < N; i++) {
      ll tmp1 = 0, tmp2 = 0, tmp3 = 0;
      tmp1 = Sum1(i, max(0ll, X-L), min(X, L));
      if(i+1 < N) tmp1 += Sum1(i+1, 0, max(0ll, L-min(X, L)));
      if(i+1 < N) tmp2 = Sum1(i+1, 0, min(X, L));
      tmp2 += Sum1(i, max(0ll, X-(L-min(L, X))), max(0ll, L-min(L, X)));
      if(i+1 < N) {
	ll lb = 0, ub = L;
	while(lb+1 < ub) {
	  ll mb = (lb+ub)/2;
	  if(Sum1(i, max(0ll, X-mb), min(X, mb))+Sum1(i+1, 0, min(X, L-mb)) > tmp1) ub = mb;
	  else lb = mb;
	}
	tmp3 = Sum1(i, X-ub, ub)+Sum1(i+1, 0, L-ub);
      }
      //cout << tmp1 << " " << tmp2 << " " << tmp3 << endl;
      ans = max({ans, tmp1, tmp2, tmp3});
    }
    cout << ans << endl;
    return 0;
  }
  ll asum[MAX_N+1] = {};
  for(int i = 0; i < N; i++) asum[i+1] = asum[i]+Sum1(i, 0, X);
  auto Sum2 = [&](int l, int r) {return asum[r]-asum[l];};
  ll l = L%X, n = L/X;
  if(l == 0) {
    n--;
    l += X;
  }
  ll ans = 0;
  for(int i = 0; i <= N-n; i++) {
    ll tmp1 = 0, tmp2 = 0, tmp3 = 0;
    if(i > 0) tmp1 = Sum1(i-1, X-l, l);
    if(i+n < N) tmp2 = Sum1(i+n, 0, l);
    if(i > 0 && i+n < N) {
      ll lb = 0, ub = l;
      while(lb+1 < ub) {
	ll mb = (lb+ub)/2;
	if(Sum1(i-1, X-mb, mb)+Sum1(i+n, 0, l-mb) > tmp1) ub = mb;
	else lb = mb;
      }
      tmp3 = Sum1(i-1, X-ub, ub)+Sum1(i+n, 0, l-ub);
    }
    ans = max(ans, Sum2(i, i+n)+max({tmp1, tmp2, tmp3}));
    //cout << i << " " << tmp1 << " " << tmp2 << " " << tmp3 << " " << Sum2(i, i+n) << " " << ans << endl;
  }
  cout << ans << endl;
  return 0;
}
