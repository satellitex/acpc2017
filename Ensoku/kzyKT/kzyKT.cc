#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef pair<int,int> P;
typedef pair<int,P> PP;

int dp1[10][1001],c[10][10],dp2[1<<10][10],dp3[2][1<<5][1001],dp[1<<10][1001],ans;
vector<PP> a[11];
int main() {
  int A,B,n;
  cin >> n >> A >> B;
  for(int k=0; k<n; k++) {
    fill(dp1[k],dp1[k]+B+1,-(1<<30));
    dp1[k][0]=0;
    int m;
    cin >> m;
    for(int i=0; i<m; i++) {
      PP p;
      cin >> p.F >> p.S.F >> p.S.S;
      int t=1;
      while(p.S.S) {
        do {
          for(int j=B; j>=0; j--) {
            if(j+p.S.F*t<=B) dp1[k][j+p.S.F*t]=max(dp1[k][j+p.S.F*t],dp1[k][j]+p.F*t);
          }
          p.S.S-=t;
        } while(p.S.S%(t*2));
        t*=2;
      }
    }
  }
  for(int i=0; i<n; i++)for(int j=0; j<n; j++) cin >> c[i][j];
  for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)c[i][j]=min(c[i][j],c[i][k]+c[k][j]);
  for(int t=0;t<(1<<n);t++)for(int i=0;i<n;i++) dp2[t][i]=1<<30;
  for(int i=0; i<n; i++) dp2[1<<i][i]=c[0][i];
  for(int t=1; t<(1<<n); t++) {
    for(int i=0; i<n; i++) {
      if(!(t&(1<<i))) continue;
      for(int j=0; j<n; j++) {
        if(t&(1<<j)) continue;
        dp2[t|(1<<j)][j]=min(dp2[t|(1<<j)][j],dp2[t][i]+c[i][j]);
      }
    }
  }
  for(int t=0;t<(1<<(n/2+1));t++)for(int i=0;i<=B;i++)dp3[0][t][i]=dp3[1][t][i]-(1<<30);
  for(int l=0; l<2; l++) {
    for(int t=0; t<(1<<(n/2+n%2*l)); t++) {
      for(int i=0; i<n/2+n%2*l; i++) {
        if(!(t&(1<<i))) continue;
        for(int j=B; j>=0; j--) {
          for(int k=B-j; k>=0; k--) {
            dp3[l][t|(1<<i)][j+k]=max(dp3[l][t|(1<<i)][j+k],dp3[l][t][j]+dp1[i+n/2][k]);
          }
        }
      }
      for(int i=0; i<B; i++) dp3[l][t][i+1]=max(dp3[l][t][i+1],dp3[l][t][i]);
    }
  }
  for(int t=0;t<(1<<n);t++)for(int i=0;i<=B;i++)dp[t][i]=-(1<<30);
  for(int t=0;t<(1<<(n/2));t++) {
    for(int s=0; s<(1<<(n/2+n%2)); s++) {
      int x=dp2[t|(s<<(n/2))][0];
      for(int i=0; i<=B; i++) ans=max(ans,dp3[0][t][i]+dp3[1][s][min(B,A-i)]);
    }
  }
  cout << ans << endl;
  return 0;
}
