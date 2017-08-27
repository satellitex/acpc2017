#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  while(n--) {
    int theta;
    cin >> theta;
    cout << theta/30 << " " << (theta%30)*2 << endl;
  }
  return 0;
}
