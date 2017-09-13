#include<bits/stdc++.h>
using namespace std;
int main(){
  int n,m,d,v,s,f,k[360]={};
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>m>>d>>v>>s;
    m--,d--;
    int day=m*30+d;
    for(int j=0;j<v;j++)k[(day+j)%360]=max(k[(day+j)%360],s);
    for(int j=1;j<s;j++){
      k[(day+v+j-1)%360]=max(k[(day+v+j-1)%360],s-j);
      f=day-j<0?360:0;
      k[(m*30+d-j+f)]=max(k[m*30+d-j+f],s-j);
    }
  }
  int ans=1000;
  for(int i=0;i<360;i++)ans=min(ans,k[i]);
  cout<<ans<<endl;
  return 0;
}
