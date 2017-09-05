#include<bits/stdc++.h>
using namespace std;
#define MAX 200005
#define SZ 500
#define INF (1000000007)
typedef pair<int,int> P;
int a[MAX];
int b[MAX];

void update(int a[MAX],int i,int x){
  a[i]=x;
}

int query(int a[MAX],int l,int r){
  int res=INF;
  for(int i=l;i<r;i++){
    res=min(res,a[i]);
  }
  return res;
}


int N,Q;

int main(){
  scanf("%d",&N);
  
  for(int i=0;i<N;i++){
    int x;
    scanf("%d",&x);
    update(a,i,x);
  }
  
  for(int i=0;i<N;i++){
    int x;
    scanf("%d",&x);
    update(b,i,x);
  }

  scanf("%d",&Q);
  while(Q--){
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    if(x==1){
      update(a,y-1,z);
    }
    if(x==2){
      update(b,y-1,z);
    }
    if(x==3){
      printf("%d\n", query(a,y-1,z) );
    }
    if(x==4){
      printf("%d\n", query(b,y-1,z) );
    }
    if(x==5){
      for(int i=0;i<N+1;i++)a[i]=b[i];
    }
    if(x==6){
      for(int i=0;i<N+1;i++)b[i]=a[i];
    }
  }
  return 0;
}

