#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll calc1(ll a,ll d,ll n) {return (a*2+(n-1)*d)*n/2;}
ll calc2(ll a,ll d,ll n) {return calc1(a,d,n+1)-calc1(a,d,n);}
ll n,m,t,a[111111],b[111111],c[111111],d[111111];

ll calc(ll k,ll mid) {
  ll sum=calc1(calc2(a[k],b[k],mid),b[k],m-mid);
  if(c[k]+t+mid>n*m) return -1;
  ll l=lower_bound(c,c+n,c[k]+t+mid)-c;
  sum+=d[l-1]-d[k+1];
  sum+=calc1(a[l-1],b[l-1],t-m*(l-k-1)+mid);
  return sum;
}

int main() {
  cin >> n >> m >> t;
  for(int i=0; i<n; i++) cin >> a[i] >> b[i];
  c[0]=d[0]=0;
  for(int i=0; i<n; i++) {
    c[i+1]+=c[i]+m;
    d[i+1]+=d[i]+calc1(a[i],b[i],m);
  }
  ll ans=0;
  for(int i=0; i<n; i++) {
    ll l=max(0LL,m-t),r=m;
    while(l+2<r) {
      ll m1=(l*2+r)/3,m2=(l+r*2)/3;
      ll d1=calc(i,m1),d2=calc(i,m2);
      if(d1<d2) l=m1;
      else r=m2;
    }
    for(int j=l; j<=r; j++) {
      ll sum=calc(i,j);
      ans=max(ans,calc(i,j));
    }
  }
  cout << ans << endl;
  return 0;
  vector<ll> v;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) v.push_back(calc2(a[i],b[i],j));
  }
  for(int i=0; i<v.size(); i++) {
    ll sum=0;
    for(int j=0; j<t; j++) {
      if(i+j>=v.size()) return 0;
      sum+=v[i+j];
    }
    cerr << i << " " << sum << " " << calc(i/m,i%m) << endl;
  }
  return 0;
}
