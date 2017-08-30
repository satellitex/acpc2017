#include <bits/stdc++.h>
#define int long long
#define N 100010
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}


signed main(){
  int n,A[N];
  cin>>n;
  for(int i=0;i<n;i++)scanf("%lld",&A[i]);
  int left = 1,right = 1;
  int ans = 1;
  for(int i=0;i<n-1;i++) {
    if(A[i] < A[i+1]) right++,left = 1;
    if(A[i] > A[i+1]) left++, right = 1;
    Max(ans,max(left,right));
  }
  cout<<ans<<endl;
  return 0;
}
