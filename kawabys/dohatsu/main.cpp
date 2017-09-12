#include<bits/stdc++.h>
using namespace std;
#define MAX_N 100005
typedef long long ll;

ll calc(ll a,ll d,ll n){
  if(n==0)return 0;
  return ( a+a+d*(n-1) )*n/2;
}

ll N,X,L;
ll a[MAX_N],d[MAX_N];

ll solve2();

ll solve(){
  
  if(L<=X)return solve2();

  ll res=0, val=0;

  
  int j=0;
  for(int i=0;i<N;i++){
    while( j < i+L/X ){
      val+=(a[j]+a[j]+(X-1)*d[j])*X/2;
      j++;
      if(j>=N)break;
    }
    res=max(res,val);
    if(j>=N)break;


    //  cout<<"i="<<i<<" j="<<j<<endl;
    //    cout<<"val="<<val<<endl;
    
    ll aj =a[j]+(L%X)*d[j];
    double A = -0.5*d[i] + 0.5*d[j];
    double B = -(a[i]-0.5*d[i]) + (aj-0.5*d[j]);
    
    double left=0, right =X-L%X , ll , rr, lv,rv;
    
    for(int p=0;p<100;p++){
      ll=(left+left+right)/3.0;
      rr=(right+right+left)/3.0;
      lv=A*ll*ll+B*ll;
      rv=A*rr*rr+B*rr;
      if(lv < rv)left=ll;
      else right=rr;
    }


    res=max(res, val + calc(a[j],d[j],L%X) );
    res=max(res, val + calc(a[j],d[j],X) - calc(a[i],d[i],X-L%X) );
    
    long long mm = left;
    /*
    cout<<"i="<<i<<" j="<<j<<endl;
    cout<<"val="<<val<<endl;
    cout<<"mm="<<mm<<endl;
    cout<<val + calc(a[j],d[j],L%X)<<endl;
    cout<<endl;
    */
    
    for( long long  dm = mm-1; dm<=mm+1; dm++ ){
      if(dm<0 || dm>(X-L%X) )continue;
      res=max(res, val + calc(a[j],d[j],L%X+dm) - calc(a[i],d[i],dm) );
    }
  
    if(i>0 && L%X>0){
      
      long long fa = a[i-1]+(X-1)*d[i-1];
      long long fd = d[i-1]*-1;
      long long sa = a[j]+(L%X-1)*d[j];
      long long sd = d[j]*-1;

      A = ( fd*fd*0.5 ) - ( sd*sd*0.5 );
      B = ( fa-fd*0.5 ) - ( sa-sd*0.5 );
      
      left=0,right=L%X;
      for(int p=0;p<100;p++){
        ll=(left+left+right)/3.0;
        rr=(right+right+left)/3.0;
        lv=A*ll*ll+B*ll;
        rv=A*rr*rr+B*rr;
        if(lv < rv)left=ll;
        else right=rr;
      }

      mm = left;
      for( long long  dm = mm-1; dm<=mm+1; dm++ ){
        if(dm<0 || dm>(L%X) )continue;
        res=max(res, val + calc(a[j],d[j],L%X) + calc(fa,fd,dm) - calc(sa,sd,dm) );
      }
      
      
    }
    val-=(a[i]+a[i]+(X-1)*d[i])*X/2;
  }
  return res;
}

int main(){
  scanf("%lld %lld %lld",&N,&X,&L);
  for(int i=0;i<N;i++){
    scanf("%lld %lld",&a[i],&d[i]);
  }
  ll ans=solve();

  for(int i=0;i<N;i++){
    a[i]= a[i]+d[i]*(X-1);
    d[i]*=-1;
  }
  printf("%lld\n",ans);
  return 0;
}

ll solve2(){
  ll res=0;
  for(int i=0;i<N;i++){
    ll A = a[i] + (X-1)*d[i];
    ll B = a[i] + (X-L)*d[i];
    ll sum = (A+B)*L/2;
    res=max(res,sum);
  }
  return res;
}
