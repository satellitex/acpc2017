#include <bits/stdc++.h>
#define int long long
#define N 15
#define MAX_A 10010
#define MAX_B 1010
using namespace std;
const int INF = 1LL<<55;
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
        Min(dp[nbit][nx], dp[bit][pos] + D[pos][nx]);
      }
}

int dp2[N][MAX_B];
void DP2(int dp[MAX_B],vector<dat> store){

  for(dat t:store){
    int a = t.a, b = t.b, c = t.c;
    for(int j=1;c>0;c-=j,j=min(j*2,c))
      for(int k=B;k>=j*a;k--) Max(dp[k],dp[k-j*a] + j * b);
    }
}

int dp3_1[1<<((N+1)/2)][MAX_B];
int dp3_2[1<<((N+1)/2)][MAX_B];
void DP3(int dp[1<<(N/2)][MAX_B],int n,int dp2[][MAX_B]){
  bool used[1<<((N+1)/2)]={};

  for(int bit = 0;bit<(1<<n);bit++){
    for(int i=0;i<B;i++) Max(dp[bit][i+1],dp[bit][i]);
    
    for(int nx=0;nx<n;nx++){
      int nbit = bit | (1<<nx);
      if((bit==nbit)||used[nbit])continue;
      used[nbit] = 1;
      for(int i=0;i<=B;i++)
        for(int j=0;i+j<=B;j++) Max(dp[nbit][i+j], dp[bit][i] + dp2[nx][j]);
    }
  }
}

int solve(){
  if(n == 1) n++,D[0][1] = INF;
  WF();
  DP1(dp1);
  for(int i=0;i<n;i++) DP2(dp2[i],stores[i]);
  int n_1 = n/2 ,n_2 = n/2 + n%2;
  DP3(dp3_1,n_1,dp2);
  DP3(dp3_2,n_2,&dp2[n_1]);
  

  int res = 0;
  for(int i=1;i<(1<<n_1);i+=2)
    for(int j=0;j<(1<<n_2);j++){
      int bit = (j<<n_1) | i;
      int B_ = min(B, A - dp1[bit][0]);
      for(int k=0;k<=B_;k++){
        int score = dp3_1[i][k] + dp3_2[j][B_ - k];
        Max(res,score);        
      }
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

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)cin>>D[i][j];


  cout<<solve()<<endl;
  
  return 0;
}
