#include <bits/stdc++.h>
using namespace std;

int main() {
  long long n,k=0;
  cin >> n;
  while(n&(1LL<<k)) k++;
  cout << (1LL<<k) << endl;
  return 0;
}
