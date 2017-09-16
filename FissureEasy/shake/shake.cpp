#include<bits/stdc++.h>
using namespace std;

int main(){
  
  int n,cnt=0;
  char m[2222][2222];
  
  cin>>n;
  
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin>>m[i][j];

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(m[i][j]=='o'){
	cnt++;
	for(int y=i;y<n&&m[y][j]=='o';y++)
	  for(int x=j;x<n&&m[y][x]=='o';x++)
	    m[y][x]='x';
      }
    }  
  }

  cout<<cnt/3<<endl;
  
  return 0;
  
}
