#include <iostream>

using namespace std;

int main() {
  int theta;
  while(cin >> theta) {
    cout << (theta/30)%12 << " " << (theta%30)*2 << endl;
  }
  return 0;
}
