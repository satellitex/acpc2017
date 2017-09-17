#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 128

int N;
char A[MAX_N][MAX_N];

int main() {
  cin >> N;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> A[i][j];
  int cnt = 0;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(A[i][j] == 'x') continue;
      cnt++;
      for(int y = i; y < N && A[y][j] == 'o'; y++) {
	for(int x = j; x < N && A[y][x] == 'o'; x++) {
	  A[y][x] = 'x';
	}
      }
    }
  }
  cout << (cnt-4)/3+1 << endl;
  return 0;
}
