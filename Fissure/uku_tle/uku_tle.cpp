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
    if(Isin(y+dy[k], x+dx[k]) && A[y+dy[k]][x+dx[k]] == 'o') return false;
  return true;
}

bool Ischeck() {
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      if(A[i][j] == 'o' && B[i][j] == 'x') return false;
  return true;
}

bool Issamemas() {
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      if(A[i][j] != B[i][j]) return false;
  return true;
}

void fillB(int x, int y, vector<Pi>& vec) {
  for(int k = 0; k < 4; k++) {
    int nx = x+dx[k], ny = y+dy[k];
    while(Isin(nx, ny) && B[ny][nx] == 'o') {
      B[ny][nx] = 'x';
      nx += dx[k], ny += dy[k];
    }
    vec.push_back(Pi(nx, ny));
  }
  B[y][x] = 'x';
}

void resetB(int x, int y, vector<Pi>& vec) {
  for(int k = 0; k < 4; k++) {
    int nx = vec[k].first-dx[k], ny = vec[k].second-dy[k];
    while(nx != x || ny != y) {
      B[ny][nx] = 'o';
      nx -= dx[k], ny -= dy[k];
    }
  }
  B[y][x] = 'o';
}

void printB() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) cout << B[i][j];
    cout << endl;
  }
  cout << endl;
}

bool solve(int x, int y, int d=0) {
  ans.push_back(Pi(x, y));
  vector<Pi> vec;
  fillB(x, y, vec);
  if(!Ischeck()) {
    ans.pop_back();
    resetB(x, y, vec);
    return false;
  }
  bool flag = false;
  for(int i = 1; i < N; i+=2) {
    for(int j = 1; j < N; j+=2) {
      if(A[i][j] == 'o' || B[i][j] == 'x') continue;
      if(!Isnewsblack(j, i)) continue;
      if(solve(j, i, d+1)) return true;
      flag = true;
    }
  }
  if(flag) {
    ans.pop_back();
    resetB(x, y, vec);
    return false;
  }
  bool issame = Issamemas();
  if(!issame) {
    ans.pop_back();
    resetB(x, y, vec);
    return false;
  }
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
    //assert(false);
    cout << -1 << endl;
    return 0;
  }

  for(int i = 1; i < N; i+=2) {
    for(int j = 1; j < N; j+=2) {
      if(A[i][j] == 'o') continue;
      if(!Isnewsblack(j, i)) continue;
      ans.clear();
      fill(B[0], B[MAX_N], 'o');
      //if(solve(j, i)) {
      bool flag = solve(j, i);
      if(flag) {
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
