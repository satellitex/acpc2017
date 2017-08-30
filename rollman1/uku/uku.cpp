#include <iostream>

using namespace std;

#define MAX_N 100000

int main() {
  int N;
  int a[MAX_N];
  cin >> N;
  for(int i = 0; i < N; i++) cin >> a[i];

  int l = 0, r = 0;
  for(int i = 1; i < N; i++) {
    if(a[i-1] < a[i]) {
      if(r == 0) r++;
      l++;
      r--;
    } else if(a[i-1] > a[i]) {
      if(l == 0) l++;
      l--;
      r++;
    }
  }
  cout << l+r+1 << endl;
  return 0;
}
