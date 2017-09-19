#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,ans=0;
  cin >> n;
  string s[n+1];
  for(int i=0; i<n; i++) {
    cin >> s[i];
    s[i]+='x';
  }
  for(int i=0; i<=n; i++) s[n]+='x';
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(s[i-1][j-1]=='o'&&s[i][j-1]=='x'&&s[i-1][j]=='x'&&s[i][j]=='x') ans++;
    }
  }
  cout << ans/3 << endl;
  return 0;
}
