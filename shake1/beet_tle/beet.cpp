#include<bits/stdc++.h>
using namespace std;
#define int long long
int nCm(int n,int m){
  int c=0;
  for(int i=0;i<m;i++){
    {
      int k=n-i;
      while(k%2==0) c++,k/=2;
    }
    {
      int k=i+1;
      while(k%2==0) c--,k/=2;
    }
  }
  return c;
}
signed main(){
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    if(nCm(n,i)>0){
      cout<<i<<endl;
      return 0;
    }
  }
  cout<<-1<<endl;
  return 0;
}
