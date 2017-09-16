#include <bits/stdc++.h>
using namespace std;

int main() {
  long long n;
  cin >> n;
  for(int i=0;;i++) {
    if(n&(1LL<<i)) continue;
    cout << (1LL<<i) << endl;
    return 0;
  }
  return 0;
}
