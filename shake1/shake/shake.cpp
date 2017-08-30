#include<bits/stdc++.h>
using namespace std;
int main(){
  long long n,cnt=0;
  cin>>n;
  n++;
  while(n%2==0)n/=2,cnt++;
  if(n==1)cout<<-1<<endl;
  else{
    n=pow(2,cnt);
    cout<<n<<endl;
  }
  return 0;
}
