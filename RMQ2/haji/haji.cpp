#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1<<18;// = 2*131072
const int MAX_N = N;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

class RMQ{
public:
  int n;
  vector<int>dat;

  //初期化
  RMQ():n(N),dat(2*N-1,INF){}
  
  //k番目の値をaに変更
  void update(int k,int a){
    k+=n-1;
    dat[k]=a;
    while(k>0){
      k=(k-1)/2;
      dat[k]=min(dat[k*2+1],dat[k*2+2]);
    }
  }

  int getDat(int k){return dat[k+n-1];}
  
  //[a,b)の最小値を求める query(a,b,0,0,n)
  int query(int a,int b,int k=0,int l=0,int r=N){
    if(r<=a||b<=l)return INF;
    if(a<=l&&r<=b)return dat[k];
    int vl=query(a,b,k*2+1,l,(l+r)/2);
    int vr=query(a,b,k*2+2,(l+r)/2,r);
    return min(vl,vr);
  }

};

class RMQ2{
public:
  vector<int>diff;
  RMQ A,B;
  
  void updateA(int k,int a){
    diff.push_back(k);
    A.update(k,a);
  }
  void updateB(int k,int b){
    diff.push_back(k);
    B.update(k,b);
  }

  int queryA(int a,int b){return A.query(a,b);}
  int queryB(int a,int b){return B.query(a,b);}

  void cpAtoB(){
    for(int idx:diff) B.update(idx,A.getDat(idx));
    diff.clear();
  }
  void cpBtoA(){
    for(int idx:diff) A.update(idx,B.getDat(idx));
    diff.clear();
  }
};


signed main(){
  int n;
  cin>>n;
  RMQ2 rmq2;
  for(int i=0,a;i<n;i++) scanf("%lld",&a),rmq2.updateA(i,a);
  for(int i=0,b;i<n;i++) scanf("%lld",&b),rmq2.updateB(i,b);
  
  int q;
  cin>>q;
  while(q--){
    int x,y,z;
    scanf("%lld %lld %lld",&x,&y,&z);
    if(x == 1) rmq2.updateA(y-1,z);
    if(x == 2) rmq2.updateB(y-1,z);
    if(x == 3) printf("%lld\n",rmq2.queryA(y-1,z));
    if(x == 4) printf("%lld\n",rmq2.queryB(y-1,z));
    if(x == 5) rmq2.cpBtoA();
    if(x == 6) rmq2.cpAtoB();
  }
  
  return 0;
}
