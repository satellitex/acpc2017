#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll sum(const ll n, const ll a, const ll d){
    return (2*a + (n-1)*d)*n/2;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, X;
    ll L;
    cin >> N >> X >> L;
    vector<ll> a(N+5, 0), d(N+5, 0);
    for(ll i = 0; i < N; i++) cin >> a[i] >> d[i];


    if(X >= L){
        ll ans = 0;
        for(ll i = 0; i < N; i++){
            ll _a = a[i] + (X-1)*d[i];
            ll _d = -d[i];
            ans = max(ans, sum(L, _a, _d) );
        }
        cout << ans << endl;
        return 0;
    }

    ll bundle = L/X;
    ll bundle_rest = L%X;
    ll bundle_sum = 0;
    if(bundle_rest == 0){
      bundle--;
      bundle_rest = X;
    }


    // Init
    for(ll i = 0; i < bundle; i++){
        bundle_sum += sum(X, a[i], d[i]);
    }

    // Leftmost
    ll ans = 0;
    //cout << "A" << endl;
    //cout << bundle << endl;
    //cout << a.size() << endl;
    ans = bundle_sum + sum(bundle_rest, a.at(bundle), d.at(bundle));
    //cout << "B" << endl;

    // Between
    for(ll removing = 0; removing < N - bundle; removing++){
        ll local_ans = 0;
        ll adding = removing + bundle;
        bundle_sum -= sum(X, a.at(removing), d.at(removing));
        bundle_sum += sum(X, a.at(adding),   d.at(adding)  );

        ll left_a  = a.at(removing), left_d  = d.at(removing);
        left_a = left_a + (X-1)*left_d;
        left_d = -left_d;

        if( removing != N - bundle - 1){
            ll right_a = a.at(adding+1), right_d = d.at(adding+1);

            // l: the number of terms used by left-side sequence.
            ll l = 0, r = bundle_rest + 1;
            while(l+1 < r){
              ll mid = (l+r)/2;
              ll sum1 = sum(mid, left_a, left_d) + sum(bundle_rest-mid, right_a, right_d);
              ll sum0 = sum(mid-1, left_a, left_d) + sum(bundle_rest-(mid-1), right_a, right_d);
              if(sum1 - sum0 > 0){
                l = mid;
              }else{
                r = mid;
              }
            }
            ll left_range = l;
            ll right_range = bundle_rest - l;
            ans = max(ans, bundle_sum + sum(left_range, left_a, left_d) + sum(right_range, right_a, right_d));

            /*
            ll l = 0, r = X;
            while(l+1 < r){
                ll mid = (l+r)/2;
                ll mid_member = left_a + (mid-1)*left_d;
                if(mid_member < right_a){
                    r = mid;
                }else{
                    l = mid;
                }
            }
            ll left_range = min(bundle_rest, l);
            ll right_range = bundle_rest - left_range;
            ans = max(ans, bundle_sum + sum(left_range, left_a, left_d) + sum(right_range, right_a, right_d));
            */
        }else{
            ans = max(ans, bundle_sum + sum(bundle_rest, left_a, left_d));
        }
    }

    // Rightmost
    /*
    cout << "A" << endl;
    cout << N-bundle-1 << endl;
    bundle_sum -= sum(X, a.at(N-bundle-1), d.at(N-bundle-1));
    cout << "b" << endl;
    bundle_sum += sum(X, a.at(N-1), d.at(N-1));
    cout << "c" << endl;
    //cout << a[N-1] + (X-1)*d[N-1] << endl;
    //cout << bundle_sum << endl;
    ans = max(ans, bundle_sum + sum(bundle_rest, a[N-bundle-1] + (X-1)*d[N-bundle-1], -d[N-bundle-1]));
    */

    cout << ans << endl;
    return 0;
}
