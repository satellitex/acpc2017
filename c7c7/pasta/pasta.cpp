#include<bits/stdc++.h>
using namespace std;
int i,j,n,m;
string s,t;
map<string,int>R;
vector<string>V,W;
main(){
  for(cin>>n>>m;i++<n;R[s]?V.push_back(s<t?s:t),R[s]--:R[t]++){
    cin>>s;
    t=s;
    reverse(t.begin(),t.end());
    if(s==t)W.push_back(s);
  }
  sort(V.begin(),V.end());
  for(auto& a:V)cout<<a,reverse(a.begin(),a.end());
  for(sort(W.begin(),W.end());j<W.size()&&W[j]==W[j+1];j+=2);
  for(W.size()&&cout<<W[j],j=V.size();j--!=0;)cout<<V[j];
  puts("");
}
