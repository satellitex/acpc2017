#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,k=1;
  cin >> n;
  int a[n];
  for(int i=0; i<n; i++) scanf("%d",&a[i]);
  while(k<n&&a[k-1]==a[k]) k++;
  if(n==k) {
    cout << 1 << endl;
    return 0;
  }
  int f=a[k-1]<a[k],x=2;
  int ans=x;
  for(int i=k+1; i<n; i++) {
    while(i<n&&a[i-1]==a[i]) i++;
    if(i==n) break;
    if(!f&&a[i-1]>a[i]||f&&a[i-1]<a[i]) x++;
    else {
      f^=1;
      x=2;
    }
    ans=max(ans,x);
  }
  cout << ans << endl;
  return 0;
}
