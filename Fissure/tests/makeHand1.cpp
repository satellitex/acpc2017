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
  ofstream fout("8_hand_1.in");
  fout<<3<<endl;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(i==1&&j==1)fout<<'o';
      else fout<<'x';
    }
    fout<<endl;
  }
  return 0;
}
