#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Seq{
  ll a;
  ll d;

  Seq():a(0),d(0){}
  Seq(const ll a, const ll d):a(a),d(d){}

  ll sum(const ll num){
    return (2*a + (num-1)*d)*num/2;
  }

  ll sum(const ll begin_idx, const ll num){
    ll aa = a + d*begin_idx;
    return (2*aa + (num-1)*d)*num/2;
  }

  ll getTerm(const ll idx){
    return a + idx*d;
  }
};

ll getSegSum(const ll num, const ll left_begin_idx, const Seq left_, const Seq right_, const ll X){
  Seq left(left_.a + left_.d*left_begin_idx, left_.d);
  Seq right = right_;

  ll res = 0;
  ll left_num = min(num, X-left_begin_idx);
  ll right_num = num-left_num;
  assert(right_num <= X);
  res += left.sum( left_num );
  res += right.sum( right_num);
  return res;
}

#ifdef EBUG
int main(void){
  Seq a(1, 1);
  Seq b(2, 2);
  for(int i = 0; i < 3; i++){
    cout << getSegSum(4, i, a, b, 3) << endl;
  }
  return 0;
}

#else
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, X;
    ll L;
    cin >> N >> X >> L;
    vector<Seq> s(N);
    for(ll i = 0; i < N; i++){
      ll a, d; cin >> a >> d;
      s[i] = Seq(a, d);
    }


    if(X >= L){
        ll ans = 0;
        for(ll i = 0; i < N; i++){
            Seq _s = Seq(s[i].a + (X-1)*s[i].d, -s[i].d);
            ans = max(ans, _s.sum(L));
        }
        cout << ans << endl;
        return 0;
    }

    ll bundle = L/X;
    ll bundle_rest = L%X;
    ll bundle_sum = 0;
    bundle--;
    bundle_rest += X;


    // Init
    for(ll i = 0; i < bundle; i++){
        bundle_sum += s[i].sum(X);
    }

    // Leftmost
    /* At the leftmost of seqence, Nothing has to be done.
     *
     * //ll ans = 0;
     * //ans = bundle_sum + sum(bundle_rest, a.at(bundle), d.at(bundle));
     */

    ll ans = 0;
    // Between
    for(ll removing = 0; removing < N - bundle - 1; removing++){
        ll local_ans = 0;
        ll adding = removing + bundle;
        bundle_sum -= s[removing].sum(X);
        bundle_sum += s[adding].sum(X);

        Seq left_s = s[removing];
        Seq right_s = s[adding+1];

        // l: the idx of terms used by right-side sequence.
        ll l = 0, r = bundle_res;
        while(l+1 < r){
          ll mid = (l+r)/2;
          /* 
           * b_mid: b_i
           * a_mid: a_(X-B+i)
           */
          ll right_idx = mid;
          ll left_idx = X-(bundle_rest-mid-1);
          ll b_mid = right_s.getTerm(right_idx);
          ll a_mid = left_s.getTerm(left_idx);
          assert(left_idx >= 0);
          cout << "(" << l << ", " << r << ")" << endl;
          cout << b_mid - a_mid + (right_s.d - left_s.d) << endl;
          if( b_mid - a_mid + (right_s.d - left_s.d) >= 0 ){
            l = mid;
          }else{
            r = mid;
          }
        }
        cout << l << endl;
        // l: the beginning of taking sum.
        //cout << "left_begin=" << left_begin << endl;
        ll left_num = bundle_rest - l - 1;
        ans = max(ans, bundle_sum + left_s.sum(X-bundle_rest+l+1, left_num) + right_s.sum(0, l+1));

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
#endif
