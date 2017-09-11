#include<bits/stdc++.h>
using namespace std;
int i,j,k,n,m,d,v,s,x[360],z,y=1e9;
main(){
  for(cin>>n;i++<n;){
    cin>>m>>d>>v>>s;
    for(j=z=--m*30+--d;j<z+v;)
      x[j%360]=max(x[j++%360],s);
    for(j=0;j<s;++j)
      x[(z-j+1080)%360]=max(x[(z-j+1080)%360],s-j),
        x[(z+j+v-1)%360]=max(x[(z+j+v-1)%360],s-j);
  }
  for(auto &a:x)
    y=min(y,a);
  /**
    for(;k<360;++k)
    x[k]-y||cout<<k/30+1<<' '<<k%30+1<<endl;
  **/
  cout<<y<<endl;
}
