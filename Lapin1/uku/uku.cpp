#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;
  int jam[360] = {};
  while(n--) {
    int m, d, v, s;
    cin >> m >> d >> v >> s;
    m--, d--;
    int x = m*30+d;
    for(int i = 0; i < v; i++) {
      jam[(x+i)%360] = max(jam[(x+i)%360], s);
    }
    for(int i = 0; i < s; i++) {
      jam[(x-i+3600)%360] = max(jam[(x-i+3600)%360], s-i);
      jam[(x+v-1+i)%360] = max(jam[(x+v-1+i)%360], s-i);
    }
  }
  int mn = 1<<25;
  for(int i = 0; i < 360; i++) {
    mn = min(mn, jam[i]);
  }
  /*
  for(int i = 0; i < 360; i++) {
    if(mn == jam[i]) {
      cout << i/30+1 << " " << i%30+1 << endl;
    }
  }
  */
  cout << mn << endl;
  return 0;
}
