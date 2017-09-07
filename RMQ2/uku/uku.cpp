#include <bits/stdc++.h>

using namespace std;

//#define int long long
#define all(v) (v).begin(), (v).end()
#define resz(v, ...) (v).clear(), (v).resize(__VA_ARGS__)
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

typedef pair<int, int> Pi;
typedef tuple<int, int, int> Ti;
typedef vector<int> vint;

const int inf = INT_MAX;//1LL << 55;
const int mod = 1e9 + 7;

struct SegmentTree {
  struct node {
    node *lch, *rch;
    int val;
    node():lch(nullptr), rch(nullptr), val(inf){}
  };
  int err;
  int sz;
  vector<node*> root;
  SegmentTree(int n) {
    err = inf;
    sz = 1;
    while(sz < n) sz <<= 1;
    root.push_back(nullptr);
  }
  int get(node *x) {
    return x ? x->val : err;
  }
  node* update(node *x, int k, int val, int l, int r) {
    x = x ? new node(*x) : new node();
    if(r-l == 1) {
      x->val = val;
      return x;
    }
    int m = (l+r)/2;
    if(k < m) x->lch = update(x->lch, k, val, l, m);
    else x->rch = update(x->rch, k, val, m, r);
    x->val = min(get(x->lch), get(x->rch));
    return x;
  }
  void update(int k, int val) {
    root.push_back(update(root.back(), k, val, 0, sz));
  }
  int query(int a, int b, node *x, int l, int r) {
    if(!x) return err;
    if(r<=a||b<=l) return err;
    if(a<=l&&r<=b) return get(x);
    int m = (l+r)/2;
    return min(query(a, b, x->lch, l, m), query(a, b, x->rch, m, r));
  }
  int query(int a, int b) {
    return query(a, b, root.back(), 0, sz);
  }
};

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int N, Q;
  cin >> N;

  vint a(N), b(N);
  rep(i, N) cin >> a[i];
  rep(i, N) cin >> b[i];

  SegmentTree s(N), t(N);
  rep(i, N) {
    s.update(i, a[i]);
    t.update(i, b[i]);
  }

  cin >> Q;
  while(Q--) {
    int x, y, z;
    cin >> x >> y >> z;
    switch(x) {
    case 1: s.update(y-1, z); break;
    case 2: t.update(y-1, z); break;
    case 3: cout << s.query(y-1, z) << endl; break;
    case 4: cout << t.query(y-1, z) << endl; break;
    case 5: s.root.push_back(t.root.back()); break;
    case 6: t.root.push_back(s.root.back()); break;
    }
  }

  return 0;
}
