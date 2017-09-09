#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define MAX_N 200000

const int inf = 1<<30;

const int A = 0;
const int B = 1;
struct SegmentTree {
  vector<int> data[2];
  int sz;
  set<int> st;
  SegmentTree(int n) {
    sz = 1; while(sz < n) sz *= 2;
    data[A].resize(2*sz-1, inf);
    data[B].resize(2*sz-1, inf);
  }
  void Set(int f, int k, int x) {
    st.insert(k);
    k += sz-1;
    data[f][k] = x;
    while(k > 0) {
      k = (k-1)/2;
      data[f][k] = min(data[f][2*k+1], data[f][2*k+2]);
    }
  }
  int Get(int f, int k) {
    return data[f][k+sz-1];
  }
  int Min(int f, int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return inf;
    if(a <= l && r <= b) return data[f][k];
    int vl = Min(f, a, b, 2*k+1, l, (l+r)/2);
    int vr = Min(f, a, b, 2*k+2, (l+r)/2, r);
    return min(vl, vr);
  }
  int Min(int f, int a, int b) {
    return Min(f, a, b, 0, 0, sz);
  }
  void To(int f, int g) {
    for(int k : st) Set(f, k, Get(g, k));
    st.clear();
  }
};

int N, Q;
int a[MAX_N];
int b[MAX_N];

int main() {
  cin >> N;
  for(int i = 0; i < N; i++) cin >> a[i];
  for(int i = 0; i < N; i++) cin >> b[i];
  SegmentTree seg(N);
  for(int i = 0; i < N; i++) seg.Set(A, i, a[i]);
  for(int i = 0; i < N; i++) seg.Set(B, i, b[i]);
  cin >> Q;
  for(int i = 0; i < Q; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    if(x == 1) seg.Set(A, y-1, z);
    else if(x == 2) seg.Set(B, y-1, z);
    else if(x == 3) cout << seg.Min(A, y-1, z) << endl;
    else if(x == 4) cout << seg.Min(B, y-1, z) << endl;
    else if(x == 5) seg.To(A, B);
    else if(x == 6) seg.To(B, A);
  }

  return 0;
}
