#include <iostream>

using namespace std;

//using ll = long long;
typedef long long ll;

int main() {
  ll n;
  while(cin >> n) {
    ll a = n+1;
    ll cnt = 0;
    while(!(a&1)) a >>= 1, cnt++;
    cout << (a == 1ll ? -1ll : 1ll<<cnt) << endl;
  }
  return 0;
}
