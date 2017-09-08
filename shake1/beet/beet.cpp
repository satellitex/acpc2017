#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
  int n;
  cin>>n;
  n++;
  int a=1;
  while(n%2==0) a*=2,n/=2;
  cout<<(n==1?-1:a)<<endl;
  return 0;
}
