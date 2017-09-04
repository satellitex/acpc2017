#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_A 10000
#define MAX_B 1000
#define MAX_N 10
#define MAX_K 100

int A, B, N;
int K[MAX_N];
int a[MAX_N][MAX_K];
int b[MAX_N][MAX_K];
int c[MAX_N][MAX_K];
int d[MAX_N][MAX_N];

int dp1[MAX_N][MAX_B+1];
int dp2[1<<MAX_N][MAX_N][MAX_N];
int dp3[1<<MAX_N][MAX_A];
int dp4[1<<MAX_N][MAX_A];

const int inf = 1<<25;

int main() {

  memset(dp1, 0, sizeof(dp1));
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < K[i]; j++) {
      int lim = c[i][j];
      for(int k = 0; lim > 0; k++) {
	int num = min(lim, 1<<k);
	int w = a[i][j]*num;
	int v = b[i][j]*num;
	for(int l = B; l >= w; l--) {
	  dp1[i][l] = max(dp1[i][l], dp1[i][l-w] + v);
	}
	lim -= num;
      }
    }
  }

  for(int k = 0; k < N; k++)
    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
	d[i][j] = min(d[i][j], d[i][k]+d[k][j]);

  for(int bit = 0; bit < 1<<N; bit++)
    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
	dp2[bit][i][j] = inf;

  for(int i = 0; i < N; i++) {
    dp2[1<<i][i][i] = 0;
    for(int bit = 0; bit < 1<<N; bit++) {
      if(!((bit>>i)&1)) continue;
      for(int j = 0; j < N; j++) {
	if(!((bit>>j)&1)) continue;
	for(int k = 0; k < N; k++) {
	  if(((bit>>k)&1) || dp2[bit][i][j] == inf) continue;
	  dp2[bit|(1<<k)][i][k] = min(dp2[bit|(1<<k)][i][k], dp2[bit][i][j]+d[j][k]);
	}
      }
    }
  }

  for(int bit = 0; bit < 1<<N; bit++)
    for(int i = 0; i <= A; i++)
      dp3[bit][i] = inf;

  int n1 = N/2;
  for(int i = 0; i <= A; i++) dp3[1<<0][i] = dp1[0][i];
  for(int bit = 0; bit < 1<<n1; bit++) {
    for(int i = 0; i < n1; i++) {
      if((bit>>i)&1) continue;
      for(int j = B; j >= 0; j--) {
	for(int k = j; k >= 0; k--) {
	  dp3[bit|(1<<i)][j] = max(dp3[bit|(1<<i)][j], dp3[bit][j-k]+dp1[i][k]);
	}
      }
    }
  }

  for(int bit = 0; bit < 1<<N; bit++)
    for(int i = 0; i <= A; i++)
      dp4[bit][i] = inf;

  int n2 = (N+1)/2;
  for(int i = 0; i <= A; i++) dp4[1<<0][i] = dp1[n1][i];
  for(int bit = 0; bit < 1<<n2; bit++) {
    for(int i = 0; i < n2; i++) {
      if((bit>>i)&1) continue;
      for(int j = B; j >= 0; j--) {
	for(int k = j; k >= 0; k--) {
	  dp4[bit|(1<<i)][j] = max(dp4[bit|(1<<i)][j], dp4[bit][j-k]+dp1[n1+i][k]);
	}
      }
    }
  }

  int ans = 0;
  for(int bit1 = 0; bit1 < 1<<n1; bit1++) {
    for(int bit2 = 0; bit2 < 1<<n2; bit2++) {
      for(int i = 0; i <= B; i++) {
	for(int j = 0; j < N; j++) {
	  int idx = A-i-dp2[bit1|(bit2<<n1)][0][j]-d[j][0];
	  if(0 <= idx && idx <= B) ans = max(ans, dp3[bit1][i]+dp4[bit2][idx]);
	}
      }
    }
  }
  cout << ans << endl;

  return 0;
}
