#include<bits/stdc++.h>

using namespace std;

typedef long long ll;


ll n,x,l,a[100000],d[100000],s[100001];



ll cal(ll a0,ll d0,ll n0){ return (2*a0+d0*(n0-1))*n0/2;}

ll check(ll p,ll f){


  if(p+(l/x)>=n)return 0;

  ll ns=p+(l/x),k=l%x;
  ll s1=s[ns-1]-s[p]+cal(a[ns],d[ns],l%x);
  ll s2=s[ns]-s[p+1]+cal(a[p]+d[p]*(x-(l%x)),d[p],l%x);
  ll res=max(s1,s2);
  
  ll l=1,r=x-k,m;

  while(l<r){
  

  }


  ll ss=(ns-1<p)?0:(s[ns-1]-s[p]);
  
  ll aa=(2*(a[p]+d[p]*r)+d[p]*(x-r-1))*(x-r)/2+
    (2*a[ns]+d[ns]*(k+r-1))*(k+r)/2+ss;

   ll bb=(2*(a[p]+d[p]*(r-1))+d[p]*(x-(r-1)-1))*(x-(r-1))/2+
    (2*a[ns]+d[ns]*(k+(r-1)-1))*(k+(r-1))/2+ss;

   if(r==1)bb=0;
   if(r==k)aa=0;

   res=max(res,max(aa,bb));
   
   return res;
}


int main(){


  cin>>n>>x>>l;

  for(int i=0;i<n;i++){
    cin>>a[i]>>d[i];
    s[i+1]=cal(a[i],d[i],x);
    s[i+1]+=s[i];
  }

  ll ans=0;

  for(int i=0;i<n;i++) {
    ans=max(ans,check(i,0));
    ans=max(ans,check(i,1));
  }
  
  cout<<ans<<endl;
  
  return 0;
}
