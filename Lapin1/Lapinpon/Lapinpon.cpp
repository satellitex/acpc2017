#include <iostream>
using namespace std;
int main(){

  int n,m,d,s,v,day[360]={};
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>m>>d>>v>>s;
    int d1=(m-1)*30+d-1;
    for(int j=0;j<v;j++){
      int tmp=(d1+j)%360;
      day[tmp]=max(day[tmp],s);
    }
    for(int j=0;j<s;j++){
      int tmp1=d1-j;
      while(tmp1<0) tmp1+=360;
      day[tmp1]=max(day[tmp1],s-j);
      int tmp2=d1+v+j;
      tmp2%=360;
      day[tmp2]=max(day[tmp2],s-j-1);
    }
  }
  int md=1001;
  for(int i=0;i<360;i++) md=min(md,day[i]);
  for(int i=0;i<360;i++) if(day[i]==md) cout<<i/30+1<<" "<<i%30+1<<endl;
  
  return 0;
  
}
