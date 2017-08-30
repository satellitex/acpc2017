#include<iostream>
#include<cmath>
using namespace std;
int main(){
  long long n,tmp,cnt=0;
  cin>>n;
  tmp=n+1;
  while(tmp%2==0)tmp/=2,cnt++;
  if(tmp==1)cout<<-1<<endl;
  else {
      n=pow(2,cnt);
      cout<<n<<endl;
    }
  return 0;
}
