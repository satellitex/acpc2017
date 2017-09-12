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
  auto Sum1 = [&](int i, int j, int n) {
    return (a[i]+j*d[i] + a[i]+(j+n-1)*d[i])*n/2;
  };
  if(L <= X) {
    ll ans = 0;
    for(int i = 0; i < N-1; i++) {
      ll sum = 0;
      for(int j = 0; j <= L; j++) sum = max(sum, Sum1(i, X-j, j)+Sum1(i+1, 0, L-j));
      ans = max(ans, sum);
    }
    cout << ans << endl;
    return 0;
  }
  ll asum[MAX_N+1] = {};
  for(int i = 0; i < N; i++) asum[i+1] = asum[i]+Sum1(i, 0, X);
  auto Sum2 = [&](int l, int r) {
    return asum[r]-asum[l];
  };
  ll l = L%X, n = L/X;
  ll ans = 0;
  for(int i = 0; i < N; i++) {
    ll sum = 0;
    for(int j = 0; j <= l; j++) sum = max(sum, Sum1(i-1, X-j, j)+Sum1(i+n, 0, l-j));
    ans = max(ans, Sum2(i, i+n)+sum);
  }
  cout << ans << endl;
  return 0;
}
