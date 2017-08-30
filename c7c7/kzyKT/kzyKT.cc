#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,m;
  cin >> n >> m;
  map<string,int> ma;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    ma[s]++;
  }
  set<string> se;
  vector<string> ans;
  string z="";
  for(map<string,int>::iterator it=ma.begin(); it!=ma.end(); it++) {
    string s=it->first;
    if(se.count(s)) continue;
    string t=s;
    reverse(t.begin(),t.end());
    if(s==t) {
      if(ma[s]%2&&z=="") z=s;
      for(int i=0; i<ma[s]/2; i++) ans.push_back(s);
    } else for(int i=0; i<min(ma[s],ma[t]); i++) ans.push_back(s);
    se.insert(t);
  }
  for(int i=0; i<ans.size(); i++) cout << ans[i];
  cout << z;
  for(int i=ans.size()-1; i>=0; i--) {
    reverse(ans[i].begin(),ans[i].end());
    cout << ans[i];
  }
  cout << endl;
  return 0;
}
