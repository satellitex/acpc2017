#include <bits/stdc++.h>
#define int long long
#define N 15
#define MAX_A 10010
#define MAX_B 1010
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}
int n,A,B;
struct dat{int a,b,c;};
vector<dat> stores[N];
int D[N][N];
void WF(){
  for(int k=0;k<n;k++)
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++) Min(D[i][j],D[i][k]+D[k][j]);
}

int dp1[1<<N][N];
void DP1(int dp[1<<N][N]){

  for(int i=0;i<(1<<N);i++)
    for(int j=0;j<N;j++) dp[i][j] = INF;
  
  dp[0][0] = 0;
  
  for(int bit = 0;bit<(1<<n);bit++)
    for(int pos = 0;pos<n;pos++)
      for(int nx = 0;nx<n;nx++){
        if(bit>>nx&1) continue;
        int nbit = bit | 1<<nx;
        Min(dp[nbit][nx],dp[bit][pos] + D[pos][nx]);
      }
}

int dp2[N][MAX_B];
void DP2(int dp[MAX_B],vector<dat> store){
  for(dat t:store){
    int a = t.a, b = t.b, c = t.c;
    for(int j=1;c>0;c-=j,j=min(j*2,c))
      for(int k=B;k>=j*a;k--) Max(dp[k],dp[k-j*a] + j * b);
    }

  for(int i=0;i<B;i++) Max(dp[i+1],dp[i]);
}

int getBit(int bit, int l,int r){
  int a = ((1<<(r))-1) & (~((1<<l)-1));
  return bit & a;
}

int dp3[1<<N][MAX_B];
int used[1<<N];
void DP3(int bit,int l,int r){
  if(used[bit]) return;
  used[bit] = 1;
  if(bit == 0 || l >= r)return;
  if(r - l == 1) return;
  int bit_1 = getBit(bit,l,(l+r)/2);
  int bit_2 = getBit(bit,(l+r)/2,r);
  if(bit_1 == bit || bit_2 == bit) used[bit]=0;

  DP3(bit_1,l,(l+r)/2), DP3(bit_2,(l+r)/2,r);

  for(int i=0;i<=B;i++)
    for(int j=0;i+j<=B;j++) Max(dp3[bit][i+j], dp3[bit_1][i] + dp3[bit_2][j]);
}

int solve(){
  WF();
  DP1(dp1);
  
  for(int i=0;i<n;i++) DP2(dp3[1<<i],stores[i]);
  int res = 0;
  for(int bit=1;bit<(1<<n);bit+=2){
    DP3(bit,0,n);
    int k = min(B,A-dp1[bit][0]);
    if(k < 0)continue;
    int score = dp3[bit][k];
    Max(res,score);
  }
  return res;  
}

signed main(){
  cin>>n>>A>>B;
  for(int i=0,k;i<n;i++){
    cin>>k;
    for(int j=0,a,b,c;j<k;j++) {
      cin>>a>>b>>c;
      stores[i].push_back((dat){a,b,c});
    }
  }

  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++) D[i][j] = INF;

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)cin>>D[i][j];


  cout<<solve()<<endl;
  
  return 0;
}
