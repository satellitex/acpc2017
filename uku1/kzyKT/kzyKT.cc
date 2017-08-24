#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef long long ll;
typedef pair<ll,ll> P;
vector<ll> v[111111];
ll d[111111];
map<P,P> ma;
P solve(ll x,ll pp) {
  if(ma.count(P(x,pp))) return ma[P(x,pp)];
  P p=P(0,0);
  for(int i=0; i<v[x].size(); i++) {
    if(pp==v[x][i]) continue;
    P q=solve(v[x][i],x);
    p.F+=q.S;
    if(q.F>q.S) p.S+=q.F;
    else p.S+=q.S;
  }
  p.F+=d[x];
  ma[P(x,pp)]=p;
  return p;
}

int main() {
  int n;
  cin >> n;
  for(int i=0; i<n; i++) cin >> d[i];
  for(int i=0; i<n-1; i++) {
    int x,y;
    cin >> x >> y;
    x--,y--;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  for(int i=0; i<n; i++) {
    P p=solve(i,-1);
    cout << p.F << endl;
  }
  return 0;
}
