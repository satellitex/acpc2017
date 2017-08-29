#include<bits/stdc++.h>
using namespace std;
typedef pair<string,string> P;
string s[1001];
bool b[1001];
vector<P>v;
vector<string>a;
int n,m;
main(){
  cin>>n>>m;
  for(int i=0;i<n;i++)cin>>s[i];

  for(int i=0;i<n;i++)if(!b[i]){
    reverse(s[i].begin(),s[i].end());

    for(int j=i+1;j<n;j++)if(!b[j]&&s[j]==s[i]){
      reverse(s[j].begin(),s[j].end());
      v.push_back(P(s[i],s[j]));
      b[j]=b[i]=1;
      break;
    }
  }
  for(int i=0;i<n;i++)if(!b[i]){
    string t=s[i];
    reverse(s[i].begin(),s[i].end());
    if(s[i]==t)a.push_back(t);
  }

  for(int i=0;i<v.size();i++)
    if(v[i].second<v[i].first)swap(v[i].first,v[i].second);

  sort(a.begin(),a.end());
  sort(v.begin(),v.end());

  for(int i=0;i<v.size();i++)cout<<v[i].first;
  if(a.size())cout<<a[0];
  for(int i=v.size()-1;i>=0;i--)cout<<v[i].second;
  cout<<endl;
}
