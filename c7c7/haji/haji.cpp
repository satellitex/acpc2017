#include <bits/stdc++.h>
#define int long long
#define N 100010
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}

bool isPalindrome(string str){
  string rstr = str; reverse(rstr.begin(),rstr.end());
  return str == rstr;
}

signed main(){
  int n,m;
  cin>>n>>m;
  
  int ans = 0;
  map<string,int> M;
  
  for(int i=0;i<n;i++){
    string str;
    cin>>str;
    string rstr = str;reverse(rstr.begin(),rstr.end());
    
    if(M[rstr]) ans+=2, M[rstr]--;
    else M[str]++;
  }

  int ok = 0;
  for(pair<string,int> p:M) ok |= (p.second!=0) && isPalindrome(p.first);
  cout<<ans+ok<<endl;
  return 0;
}
