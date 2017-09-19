#include<bits/stdc++.h>
using namespace std;
template <typename T,typename E>
struct SegmentTree{
  typedef function<T(T,T)> F;
  typedef function<T(T,E)> G;
  typedef function<E(E,E)> H;
  typedef function<E(E,int)> P;
  int n;
  F f;
  G g;
  H h;
  P p;
  T d1;
  E d0;
  vector<T> dat;
  vector<E> laz;
  SegmentTree(int n_,F f,G g,H h,P p,T d1,E d0){
    this->f=f;
    this->g=g;
    this->h=h;
    this->p=p;
    this->d1=d1;
    this->d0=d0;
    init(n_);
  }
  SegmentTree(int n_,F f,G g,H h,P p,T d1,E d0,vector<T> v){
    this->f=f;
    this->g=g;
    this->h=h;
    this->p=p;
    this->d1=d1;
    this->d0=d0;
    init(n_);
    build(n_,v);
  }
  void init(int n_){
    n=1;
    while(n<n_) n*=2;
    dat.clear();
    dat.resize(2*n-1,d1);
    laz.clear();
    laz.resize(2*n-1,d0);
  }
  void build(int n_, vector<T> v){
    for(int i=0;i<n_;i++) dat[i+n-1]=v[i];
    for(int i=n-2;i>=0;i--)
      dat[i]=f(dat[i*2+1],dat[i*2+2]);
  }
  inline void eval(int len,int k){
    if(k*2+1<n*2-1){
      laz[k*2+1]=h(laz[k*2+1],laz[k]);
      laz[k*2+2]=h(laz[k*2+2],laz[k]);
    }
    dat[k]=g(dat[k],p(laz[k],len));
    laz[k]=d0;
  }
  T update(int a,int b,E x,int k,int l,int r){
    eval(r-l,k);
    if(r<=a||b<=l) return g(dat[k],p(laz[k],r-l));
    if(a<=l&&r<=b){
      laz[k]=h(laz[k],x);
      return g(dat[k],p(laz[k],r-l));
    }
    return dat[k]=f(update(a,b,x,k*2+1,l,(l+r)/2),
		    update(a,b,x,k*2+2,(l+r)/2,r));
  }
  T update(int a,int b,E x){
    return update(a,b,x,0,0,n);
  }
  T query(int a,int b,int k,int l,int r){
    eval(r-l,k);
    if(r<=a||b<=l) return d1;
    if(a<=l&&r<=b) return dat[k];
    T vl=query(a,b,k*2+1,l,(l+r)/2);
    T vr=query(a,b,k*2+2,(l+r)/2,r);
    return f(vl,vr);
  }
  T query(int a,int b){
    return query(a,b,0,0,n);
  }
  void update(int k,T x){
    k+=n-1;
    assert(dat[k].first==x.first||dat[k].second==x.second);
    dat[k]=x;
    while(k){
      k=(k-1)/2;
      assert(laz[k]==d0);
      assert(laz[k*2+1]==d0);
      assert(laz[k*2+2]==d0);
      dat[k]=f(dat[k*2+1],dat[k*2+2]);
    }
  }
};
signed main(){
  int n;
  //cin>>n;
  scanf("%d",&n);
  typedef pair<int,int> P;
  vector<P> v(n);
  //for(int i=0;i<n;i++) cin>>v[i].first;
  //for(int i=0;i<n;i++) cin>>v[i].second;
  for(int i=0;i<n;i++) scanf("%d",&v[i].first);
  for(int i=0;i<n;i++) scanf("%d",&v[i].second);
  SegmentTree<P,P> rmq(n,
		       [](P a,P b){
			 return P(min(a.first,b.first),
				  min(a.second,b.second));
		       },
		       [](P a,P b){
			 if(b.first<0){
			   if(b.second<0) return a;
			   return P(a.second,a.second);
			 }
			 if(b.second<0)
			   return P(a.first,a.first);
			 if(b.second<b.first)
			   return P(a.second,a.second);
			 return P(a.first,a.first);
		       },
		       [](P a,P b){
			 int x=a.first,y=a.second;
			 if(x<0) x=b.first;
			 if(y<0) y=b.second;
			 return P(x,y);
		       },
		       [](P a,int k){
			 return a;
		       },
		       P(INT_MAX,INT_MAX),P(-1,-1),v);
  int q;
  //cin>>q;
  scanf("%d",&q);
  for(int i=0;i<q;i++){
    int x,y,z;
    //cin>>x>>y>>z;
    scanf("%d %d %d",&x,&y,&z);
    y--;
    if(x==1){
      assert(0<=y&&y<n);
      P c=rmq.query(y,y+1);
      c.first=z;
      rmq.update(y,c);
    }
    if(x==2){
      assert(0<=y&&y<n);
      P c=rmq.query(y,y+1);
      c.second=z;
      rmq.update(y,c);
    }
    if(x==3){
      assert(0<=y&&y<z);
      P c=rmq.query(y,z);
      //cout<<c.first<<endl;
      printf("%d\n",c.first);
    }
    if(x==4){
      assert(0<=y&&y<z);
      P c=rmq.query(y,z);
      //cout<<c.second<<endl;
      printf("%d\n",c.second);
    }
    if(x==5){
      rmq.query(0,rmq.n);
      rmq.update(0,rmq.n,P(-1,i));
    }
    if(x==6){
      rmq.query(0,rmq.n);
      rmq.update(0,rmq.n,P(i,-1));
    }
    /*//
    if(x==3||x==4) continue;
    cout<<i<<":"<<endl;
    for(int j=0;j<n;j++)
      cout<<rmq.query(j,j+1).first<<" ";
    cout<<endl;
    for(int j=0;j<n;j++)
      cout<<rmq.query(j,j+1).second<<" ";
    cout<<endl;
    //*/
    /*//
    if(x==5||x==6){
      for(int j=0;j<n;j++){
	P c=rmq.query(i,i+1);
	assert(c.first==c.second);
      }
    }
    //*/
  }
  return 0;
}
