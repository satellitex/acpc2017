#include <bits/stdc++.h>

using namespace std;

#define MAX_N 50

using Pi = pair<int, int>;

int N;
char A[MAX_N][MAX_N];

const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

bool isIn(int y, int x, int sy, int sx, int ty, int tx) {
  return sy<=y&&y<ty&&sx<=x&&x<tx;
}

Pi select(int y, int x, int k, int sy, int sx, int ty, int tx) {
  Pi res = Pi(-1, -1);
  int ny = y+dy[k], nx = x+dx[k];
  while(1) {
    while(isIn(ny, nx, sy, sx, ty, tx)) {
      if(A[ny][nx] == 'x') break;
      ny += dy[k];
    }
    while(isIn(ny, nx, sy, sx, ty, tx)) {
      if(A[ny][nx] == 'x') break;
      nx += dx[k];
    }
  }
  return res;
}

Pi buildTree(int sy, int sx, int ty, int tx) {
  assert(sy%2 == 0 && sx%2 == 0 && ty%2 == 1 && tx%2 == 1);

}

bool input() {
  cin >> N;
  assert(N <= MAX_N);
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> A[i][j];

  for(int i = 0; i < N; i+=2)
    for(int j = 0; j < N; j+=2)
      if(A[i][j] == 'x') return false;

  return true;
}

bool solve() {
  if(!input()) return false;
  Pi s = buildTree(0, 0, N, N);
  if(s.first == -1) return false;
  return true;
}

int main() {
  if(solve()) {
  } else {
    cout << -1 << endl;
  }
  return 0;
}
