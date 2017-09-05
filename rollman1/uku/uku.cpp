#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_N 100000

int main() {
  int N;
  int a[MAX_N];
  cin >> N;
  for(int i = 0; i < N; i++) cin >> a[i];
  vector<int> vec;
  vec.push_back(a[0]);
  for(int i = 1; i < N; i++) {
    if(a[i] != vec.back()) vec.push_back(a[i]);
  }
  int m = vec.size();
  int cnt = 0, ans = 1;
  for(int i = 1; i < m; i++) {
    if(vec[i-1] < vec[i]) {
      cnt = 0;
      while(i < m && vec[i-1] < vec[i]) cnt++, i++;
      i--;
    } else if(vec[i-1] > vec[i]) {
      cnt = 0;
      while(i < m && vec[i-1] > vec[i]) cnt++, i++;
      i--;
    }
    ans = max(ans, cnt+1);
  }
  cout << ans << endl;

  return 0;
}
