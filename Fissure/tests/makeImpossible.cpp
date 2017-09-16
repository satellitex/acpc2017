#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;
int N=2047;

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

string i2s(int i){
  char str[100];
  sprintf(str,"%02d",i);
  return string(str);
}
std::mt19937 mt( (int)time(0) );

void solve(int ID){


  ofstream fout("2_cimpossible_"+i2s(ID)+".in");


  mat A( N, vec( N ,0) );

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(i%2==0&&j%2==0)continue;
      if(i%2==j%2)A[i][j]=1;
    }
  }

  fout<<A.size()<<endl;
  for(int i=0;i<A.size();i++){
    for(int j=0;j<A.size();j++){
      fout<< (A[i][j]?'x':'o') ;
    }
    fout<<endl;
  }

}

int main(){
  for(int i=0;i<1;i++){
    solve(i);
  }
}
