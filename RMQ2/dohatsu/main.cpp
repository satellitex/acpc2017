#include<bits/stdc++.h>
using namespace std;
#define MAX 300005
#define SZ 500
#define INF (1000000007)
typedef pair<int,int> P;
int a[MAX];
int A[MAX];
int b[MAX];
int B[MAX];
vector< P > ma,mb,mA,mB;

void update(int a[MAX],int A[MAX],vector< P > &ma,vector< P > &mA,int i,int x){
  int I=i/SZ;

  ma.push_back( P(i,a[i]) );
  a[i]=x;
  ma.push_back( P(i,a[i]) );
  
  int mini=INF;
  for(int i=0;i<SZ;i++){
    mini=min(mini, a[ I*SZ + i ] );
  }

  mA.push_back( P(I,A[I]) );
  A[I]=mini;
  mA.push_back( P(I,A[I]) );
}

int query(int a[MAX],int A[MAX],int l,int r){
  int res=INF;
  int i=l;
  while(i<r){
    if(i%SZ==0 && i+SZ <= r){
      res=min(res,A[i/SZ]);
      i+=SZ;
    }else{
      res=min(res,a[i]);
      i++;
    }
  }
  return res;
}


void q5(){
  reverse(ma.begin(),ma.end());
  for(int i=0;i<(int)ma.size();i++){
    P p=ma[i];
    a[ p.first ] = p.second;
  }
  reverse(mA.begin(),mA.end());
  for(int i=0;i<(int)mA.size();i++){
    P p=mA[i];
    A[ p.first ] = p.second;
  }
  
  for(int i=0;i<(int)mb.size();i++){
    P p=mb[i];
    a[ p.first ] = p.second;
  }
  for(int i=0;i<(int)mB.size();i++){
    P p=mB[i];
    A[ p.first ] = p.second;
  }
  
  ma.clear();
  mA.clear();
  mb.clear();
  mB.clear();
}

void q6(){
  reverse(mb.begin(),mb.end());
  for(int i=0;i<(int)mb.size();i++){
    P p=mb[i];
    b[ p.first ] = p.second;
  }
  reverse(mB.begin(),mB.end());
  for(int i=0;i<(int)mB.size();i++){
    P p=mB[i];
    B[ p.first ] = p.second;
  }
  
  for(int i=0;i<(int)ma.size();i++){
    P p=ma[i];
    b[ p.first ] = p.second;
  }
  for(int i=0;i<(int)mA.size();i++){
    P p=mA[i];
    B[ p.first ] = p.second;
  }
  
  ma.clear();
  mA.clear();
  mb.clear();
  mB.clear();
}
int N,Q;

int main(){
  scanf("%d",&N);
  
  for(int i=0;i<N;i++){
    int x;
    scanf("%d",&x);
    update(a,A,ma,mA,i,x);
  }
  
  for(int i=0;i<N;i++){
    int x;
    scanf("%d",&x);
    update(b,B,mb,mB,i,x);
  }

  scanf("%d",&Q);
  while(Q--){
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    if(x==1){
      update(a,A,ma,mA,y-1,z);
    }
    if(x==2){
      update(b,B,mb,mB,y-1,z);
    }
    if(x==3){
      printf("%d\n", query(a,A,y-1,z) );
    }
    if(x==4){
      printf("%d\n", query(b,B,y-1,z) );
    }
    if(x==5){
      q5();
    }
    if(x==6){
      q6();
    }
  }
  return 0;
}

