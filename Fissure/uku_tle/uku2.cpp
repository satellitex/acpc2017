#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <utility>
#include <map>
#include <tuple>
#include <queue>

using namespace std;

using Pi = pair<int, int>;

#define MAX_N 50

int N;
char A[MAX_N][MAX_N];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool Isin(int x, int y, int sx, int sy, int tx, int ty) {
  return sx<=x&&x<tx&&sy<=y&&y<ty;
}

bool fillA(int x, int y, int sx, int sy, int tx, int ty) {
  if(A[y][x] == 'o') return false;
  for(int k = 0; k < 4; k++) {
    int nx = x+dx[k], ny = y+dy[k];
    while(Isin(nx, ny, sx, sy, tx, ty)) {
      if(A[ny][nx] == 'o') return false;
      nx += dx[k], ny += dy[k];
    }
  }
  return true;
}

void pushAns(vector<Pi>& v, vector<Pi>& w) {
  for(Pi p : w) v.push_back(p);
}

vector<Pi> none{Pi(-1, -1)};
vector<Pi> zero{};
using Ti = tuple<int, int, int, int>;
map<Ti, vector<Pi> > mp;
/*
vector<Pi> solve(int sx, int sy, int tx, int ty) {
  //cout << sx << " " << sy << " " << tx << " " << ty << endl;
  assert(sx%2 == 0 && sy%2 == 0 && tx%2 == 1 && ty%2 == 1);
  Ti idx = Ti(sx, sy, tx, ty);
  if(sx+1 == tx && sy+1 == ty) return zero;
  if(mp.count(idx)) return mp[idx];
  vector<Pi> res;
  bool flag = false;
  for(int i = sy+1; i < ty; i+=2) {
    for(int j = sx+1; j < tx; j+=2) {
      if(!fillA(j, i, sx, sy, tx, ty)) continue;
      res.push_back(Pi(j, i));
      auto a = solve(sx, sy, j, i);
      auto b = solve(j+1, sy, tx, i);
      auto c = solve(sx, i+1, j, ty);
      auto d = solve(j+1, i+1, tx, ty);
      if((a.empty() || a.back().first != -1) &&
	 (b.empty() || b.back().first != -1) &&
	 (c.empty() || c.back().first != -1) &&
	 (d.empty() || d.back().first != -1)) {
	pushAns(res, a);
	pushAns(res, b);
	pushAns(res, c);
	pushAns(res, d);
	mp[idx] = res;
	return res;
      }
      res.pop_back();
      flag = true;
    }
  }
  if(flag) return none;
  for(int i = sy; i < ty; i++)
    for(int j = sx; j < tx; j++)
      if(A[i][j] == 'x') return none;

  return zero;
}
*/

vector<Pi> solve(int SX, int SY, int TX, int TY) {
  priority_queue<Ti, vector<Ti>, greater<Ti> > que;
  que.emplace(Ti(SX, SY, TX, TY));
  mp[Ti(SX, SY, TX, TY)] = zero;
  while(!que.empty()) {
    Ti t = que.top(); que.pop();
    int sx, sy, tx, ty;
    tie(sx, sy, tx, ty) = t;
    assert(sx%2 == 0 && sy%2 == 0 && tx%2 == 1 && ty%2 == 1);

  }
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

  auto ans = solve(0, 0, N, N);
  if(!ans.empty()) {
    cout << ans.size() << endl;
    for(Pi p : ans) {
      cout << p.second+1 << endl;
      cout << p.first+1 << endl;
    }
  } else {
    cout << -1 << endl;
  }

  return 0;
}
