#include<bits/stdc++.h>
using namespace std;
int main(){
  long long n,ans=1;
  cin>>n;
  n++;
  while(n%2==0)n/=2,ans*=2;
  cout<<ans<<endl;
  return 0;
}
