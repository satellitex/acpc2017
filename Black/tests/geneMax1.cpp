#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;

bool inField(mat &A,int y,int x){
  int N=A.size();
  return (0<=y&&y<N && 0<=x&&x<N);
}

void put(mat &A,int y,int x){
  int dy[]={-1,0,1,0};
  int dx[]={0,1,0,-1};


  for(int i=0;i<4;i++){
    int py=y,px=x;
    A[py][px]=0;
    
    while( inField(A,py,px) && A[py][px]==0){
      A[py][px]=1;
      py+=dy[i];
      px+=dx[i];
    }
  }
  
}

int main(){
  ofstream fout("5_max_1.in");

  mat A( 3, vec(3,0) );
  put(A,1,1);

  int size=3;
  for(int i=0;i<8;i++){
    int nsize=size*2+1;
    mat tmp( nsize, vec(nsize,0) );
    
    for(int j=0;j<size;j++){
      for(int k=0;k<size;k++){
        tmp[j][k]=A[j][k];
        tmp[j+size+1][k]=A[j][k];
        tmp[j][k+size+1]=A[j][k];
        tmp[j+size+1][k+size+1]=A[j][k];
      }
    }

    put(tmp,size,size);

    size=nsize;
    A=tmp;
  }

  fout<<A.size()<<endl;
  for(int i=0;i<A.size();i++){
    for(int j=0;j<A.size();j++){
      fout<< (A[i][j]?'x':'o') ;
    }
    fout<<endl;
  }
  return 0;
}
