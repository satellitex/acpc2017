#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, X;
    ll L;
    cin >> N >> X >> L;
    vector<ll> a(N+5, 0), d(N+5, 0);
    for(ll i = 0; i < N; i++) cin >> a[i] >> d[i];
    vector<ll> seq(N*X);
    int i = 0;
    while(i < seq.size()){
      for(int j = 0; j < N; j++){
        for(int k = 0; k < X; k++){
          seq.at(i) = a.at(j) + d.at(j)*k;
          i++;
        }
      }
    }
    ll ans = 0;
    for(int i = 0; i < seq.size() - L + 1; i++){
      ll loc = 0;
      for(int j = 0; j < L; j++){
        loc += seq[i+j];
      }
      ans = max(ans, loc);
    }
    cout << ans << endl;
    return 0;
}
