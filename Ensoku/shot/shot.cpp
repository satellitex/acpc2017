#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back 
#define mp make_pair
#define fr first
#define sc second
#define Rep(i, n) for( int i = 0; i < (n); i++ )
#define Rrep(i, a, n) for( int i = (a); i < (n); i++ )
#define All(v) v.begin(), v.end()

typedef pair<int, int> Pii; 
typedef pair<int, Pii> Pip;
const int INF = 100000;
const int MAX_N = 14;

struct Shop {
  int a, b, c;
};

int N, A, B;
int K[MAX_N];
Shop data[MAX_N][100];
int d[MAX_N][MAX_N];
int min_cost[1<<MAX_N]; // cost[i][j] : iの状態で家に帰ったときの最小コスト
bool used[1<<MAX_N][MAX_N];
int dp1[1<<MAX_N][1001]; // 駄菓子屋０〜５までを使った時の最大満足度
int dp2[1<<MAX_N][1001]; // 駄菓子屋６〜１０

void calc_cost() {
  priority_queue<Pip, vector<Pip>, greater<Pip> > q; // fr : cost, sc.fr : bit, sc.sc : node
  q.push(Pip(0, Pii(1, 0)));
  while ( !q.empty() ) {
    Pip p = q.top(); q.pop();
    int c = p.fr, s = p.sc.fr, n = p.sc.sc;
    // cout << c << " " << s << " " << n << endl;
    if ( n == 0 ) min_cost[s] = min(min_cost[s], c);

    if ( used[s][n] ) continue;
    used[s][n] = true;

    Rep(i, N) {
      if ( i == n ) continue;
      q.push(Pip(c+d[n][i], Pii(s | (1<<i), i)));
    }
  }
}
 
signed main() {
  cin >> N >> A >> B;
  Rep(i, N) {
    cin >> K[i];
    Rep(j, K[i]) {
      int a, b, c;
      cin >> a >> b >> c;
      data[i][j] = {a, b, c};
    }
  }

  Rep(i, N) Rep(j, N) cin >> d[i][j];

  fill_n(min_cost, 1<<MAX_N, INF);
  memset(dp1, 0, sizeof(dp1));
  memset(dp2, 0, sizeof(dp2));
  
  calc_cost();
    
  int deq[1001];
  int deqv[1001];
  Rep(b, 1<<(MAX_N/2)) Rep(i, (MAX_N/2)) {
    if ( !((1<<i) & b) ) continue;
    Rep(j, K[i]) {
      int cost = data[i][j].a, satis = data[i][j].b, stock = data[i][j].c;
      Rep(a, cost) {
	int s = 0, t = 0;
	for ( int k = 0; k*cost+a <= 1000; k++ ) {
	  int val = dp1[b][k*cost+a] - k * satis;	  
	  while ( s < t && deqv[t-1] <= val ) t--;
	  deq[t] = k;
	  deqv[t++] = val;
	  dp1[b][k*cost+a] = deqv[s] + k * satis;
	  if ( deq[s] == k - stock ) s++; 
	}
      }
    }
  }
  
  Rep(x, 1<<(MAX_N/2)) Rrep(i, (MAX_N/2), MAX_N) {
    int b = x << (MAX_N/2);
    if ( !((1<<i) & b) ) continue;
    Rep(j, K[i]) {
      int cost = data[i][j].a, satis = data[i][j].b, stock = data[i][j].c;
      Rep(a, cost) {
	int s = 0, t = 0;
	for ( int k = 0; k*cost+a <= 1000; k++ ) {
	  int val = dp2[b][k*cost+a] - k * satis;	  
	  while ( s < t && deqv[t-1] <= val ) t--;
	  deq[t] = k;
	  deqv[t++] = val;
	  dp2[b][k*cost+a] = deqv[s] + k * satis;
	  if ( deq[s] == k - stock ) s++; 
	}
      }
    }
  }
  
  int ans = 0;
  Rep(i, 1<<(MAX_N/2)) Rep(x, 1<<(MAX_N/2)) {
    int j = x << (MAX_N/2);
    int money = min(A-min_cost[i+j], B);
    if ( money < 0 || min_cost[i+j] == INF ) continue;
    Rep(k, money+1) {
      ans = max(ans, dp1[i][k] + dp2[j][money-k]); 
    }
  }

  cout << ans << endl;
  return 0;
}
