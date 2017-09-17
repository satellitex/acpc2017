#include <bits/stdc++.h>
#define int long long
#define N 1010
using namespace std;
const int INF = 1LL<<55;
const int mod = 360;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

signed main(){
  int n;
  cin>>n;

  int A[mod] = {};
  while(n--){
    int m,d,v,s;
    cin>>m>>d>>v>>s;
    v--;
    int idx = (m-1)*30 + d-1;
    for(int i=idx;i<=idx+v;i++) Max(A[i%mod],s); 
    for(int i=0;i<s;i++) Max(A[(idx-i+10*mod)%mod],s-i);
    for(int i=0;i<s;i++) Max(A[(idx+v+i)%mod],s-i);
  }
  
  int ans = *min_element(A,A+mod);
  cout<<ans<<endl;  
  return 0;
}
