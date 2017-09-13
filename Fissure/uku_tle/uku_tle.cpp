#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <utility>

using namespace std;

using Pi = pair<int, int>;

#define MAX_N 50

int N;
char A[MAX_N][MAX_N];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

char B[MAX_N][MAX_N];
vector<Pi> ans;

bool Isin(int x, int y) {
  return 0<=x&&x<N&&0<=y&&y<N;
}

bool Isnewsblack(int x, int y) {
  for(int k = 0; k < 4; k++)
    if(A[y+dy[k]][x+dx[k]] == 'o') return false;
  return true;
}

bool Ischeck() {
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      if(A[i][j] == 'o' && B[i][j] == 'x') return false;
  return true;
}

void solve(int x, int y) {
  ans.push_back(Pi(x, y));
  for(int k = 0; k < 4; k++) {
    int nx = x+dx[k], ny = y+dy[k];
    while(Isin(nx, ny) && B[ny][nx] == 'o') {
      B[ny][nx] = 'x';
      nx += dx[k], ny += dy[k];
    }
  }
  B[y][x] = 'x';
  if(!Ischeck()) return;
  for(int i = 1; i < N; i+=2) {
    for(int j = 1; j < N; j+=2) {
      if(A[i][j] == 'o' || B[i][j] == 'x') continue;
      if(!Isnewsblack(j, i)) continue;
      solve(j, i);
    }
  }
}

bool Issamemas() {
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      if(A[i][j] != B[i][j]) return false;
  return true;
}

int main() {
  cin >> N;
  assert(N <= 50);
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> A[i][j];

  bool isimpossible = false;
  for(int i = 0; i < N; i+=2)
    for(int j = 0; j < N; j+=2)
      if(A[i][j] == 'x') isimpossible = true;
  if(isimpossible) {
    cout << -1 << endl;
    return 0;
  }

  for(int i = 1; i < N; i+=2) {
    for(int j = 1; j < N; j+=2) {
      if(A[i][j] == 'o') continue;
      if(!Isnewsblack(j, i)) continue;
      ans.clear();
      fill(B[0], B[MAX_N], 'o');
      solve(j, i);
      if(Issamemas()) {
	cout << ans.size() << endl;
	for(Pi p : ans) {
	  cout << p.second+1 << endl;
	  cout << p.first+1 << endl;
	}
	return 0;
      }
    }
  }
  cout << -1 << endl;

  return 0;
}
