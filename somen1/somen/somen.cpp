#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin >> n;
  for(int i=0;i<n;i++){
    int a;
    cin >> a;
    a*=2;
    cout << a/60 << " " << a%60 << endl;
  }
  return 0;
}

 
