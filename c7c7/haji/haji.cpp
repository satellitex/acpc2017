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

string rev(string str){reverse(str.begin(),str.end());return str;}
bool isPalindrome(string str){return str == rev(str);}

signed main(){
  int n,m;
  cin>>n>>m;
  
  map<string,int> M;
  vector<string> parts; 
  for(int i=0;i<n;i++){
    string str;
    cin>>str;
    string rstr = rev(str);
    if(M[rstr]) M[rstr]--,parts.push_back(min(str,rstr));
    else M[str]++;
  }
  sort(parts.begin(),parts.end());
  
  string med;
  for(pair<string,int> p:M) if(med == "" && p.second>0 && isPalindrome(p.first)) med = p.first;

  string ans;  
  for(string s:parts) ans += s;
  ans = ans + med + rev(ans);
  cout<<ans<<endl;
  return 0;
}
