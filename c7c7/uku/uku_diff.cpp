#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define MAX_N 1000

int main() {
  int N, M;
  cin >> N >> M;
  string s[MAX_N+1], t[MAX_N+1];
  map<string, int> mp;
  map<string, int> rmp;
  for(int i = 0; i < N; i++) cin >> s[i];
  s[N] = ""; N++;
  sort(s, s+N);

  for(int i = 0; i < N; i++) {
    t[i] = s[i];
    reverse(t[i].begin(), t[i].end());
    if(mp.count(t[i])) rmp[t[i]]++;
    else mp[s[i]]++;
  }

  string ans = "";
  for(int i = 0; i < N; i++) {
    if(!mp.count(s[i])) continue;
    if(s[i] != t[i]) continue;
    if(s[i].size() == 1 && rmp[s[i]] > 0) rmp[s[i]]--;
    else mp[s[i]]--;
    string sum = "";
    for(auto& p : mp) {
      if(p.second > 0 && rmp[p.first] > 0) {
	int num = (p.first.size() == 1 ? (p.second+rmp[p.first])/2 : min(p.second, rmp[p.first]));
	for(int j = 0; j < num; j++) sum += p.first;
      }
    }
    string rsum = sum;
    reverse(rsum.begin(), rsum.end());
    string tmp = sum+s[i]+rsum;
    if(ans.size() < tmp.size()) ans = tmp;
    else if(ans.size() == tmp.size() && ans > tmp) ans = tmp;
    if(s[i].size() > 1 || mp[s[i]] == 0) mp[s[i]]++;
    else rmp[s[i]]++;
  }
  cout << ans << endl;

  return 0;
}
