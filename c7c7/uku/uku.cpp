#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

#define MAX_N 1000

int N, M;
string s[MAX_N];
string t[MAX_N];
bool used[MAX_N];

int main() {
  cin >> N >> M;
  for(int i = 0; i < N; i++) cin >> s[i];
  sort(s, s+N);
  vector<string> vec;
  for(int i = 0; i < N; i++) {
    if(used[i]) continue;
    t[i] = s[i];
    reverse(t[i].begin(), t[i].end());
    for(int j = i+1; j < N; j++) {
      if(used[j] || s[j] != t[i]) continue;
      t[j] = s[i];
      vec.push_back(s[i]);
      used[i] = used[j] = true;
      break;
    }
  }
  sort(vec.begin(), vec.end());
  string c = "";
  for(int i = 0; i < N; i++) {
    if(used[i] || s[i] != t[i]) continue;
    if(c.size() < s[i].size() ||
       (c.size() == s[i].size() && c > s[i])) c = s[i];
  }
  string pre = "";
  for(string& str : vec) pre += str;
  string suf = pre;
  reverse(suf.begin(), suf.end());
  cout << pre << c << suf << endl;

  return 0;
}
