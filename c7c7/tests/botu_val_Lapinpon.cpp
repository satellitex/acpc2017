#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int main(){

  int n,m;
  string s;
  cin>>n>>m;
  if(n<1||n>1000||m<1||m>30) exit(1);
  for(int i=0;i<n;i++){
    cin>>s;
    if(s.size()!=m) exit(1);
    for(int j=0;j<s.size();j++) if(!('a'<=s[j]&&s[j]<='z')) exit(1);
  }
  if(cin>>n) exit(1); 
  
}			     
