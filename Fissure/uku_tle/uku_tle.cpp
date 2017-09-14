#include <bits/stdc++.h>

using namespace std;

#define MAX_N 50

int N;
char A[MAX_N][MAX_N];

const int dy[] = {1, 0, -1, 0};
const int dx[] = {0, 1, 0, -1};

bool isIn(int y, int x, int sy, int sx, int ty, int tx) {
  return sy<=y&&y<ty&&sx<=x&&x<tx;
}

bool isFillA(int y, int x, int sy, int sx, int ty, int tx) {
  if(A[y][x] == 'o') return false;
  for(int k = 0; k < 4; k++) {
    int ny = y+dy[k], nx = x+dx[k];
    while(isIn(ny, nx, sy, sx, ty, tx)) {
      if(A[ny][nx] == 'o') return false;
      ny += dy[k], nx += dx[k];
    }
  }
  return true;
}

bool isExistBlack(int sy, int sx, int ty, int tx) {
  for(int i = sy; i < ty; i++)
    for(int j = sx; j < tx; j++)
      if(A[i][j] == 'x') return true;
  return false;
}

using Pi = pair<int, int>;
using Ti = tuple<int, int, int, int>;
map<Ti, Pi> mp;
map<Pi, vector<Pi>> graph;
Pi solve(int sy, int sx, int ty, int tx) {
  assert(sy%2 == 0 && sx%2 == 0 && ty%2 == 1 && tx%2 == 1);
  assert(sy < ty && sx < tx);
  Ti idx = Ti(sy, sx, ty, tx);
  if(mp.count(idx)) return mp[idx];
  if(!isExistBlack(sy, sx, ty, tx)) return mp[idx] = Pi(-1, -1);
  for(int i = sy+1; i < ty; i+=2) {
    for(int j = sx+1; j < tx; j+=2) {
      if(!isFillA(i, j, sy, sx, ty, tx)) continue;
      Pi p = Pi(i, j);
      Pi a = solve(sy, sx, i, j);
      if(a.first == -2) continue;
      Pi b = solve(sy, j+1, i, tx);
      if(b.first == -2) continue;
      Pi c = solve(i+1, sx, ty, j);
      if(c.first == -2) continue;
      Pi d = solve(i+1, j+1, ty, tx);
      if(d.first == -2) continue;
      graph[p].clear();
      if(a.first != -1) graph[p].push_back(a);
      if(b.first != -1) graph[p].push_back(b);
      if(c.first != -1) graph[p].push_back(c);
      if(d.first != -1) graph[p].push_back(d);
      return mp[idx] = p;
    }
  }
  return mp[idx] = Pi(-2, -2);
}

char B[MAX_N][MAX_N];

bool fillB(int y, int x) {
  if(B[y][x] == 'x') return false;
  for(int k = 0; k < 4; k++) {
    int ny = y+dy[k], nx = x+dx[k];
    while(isIn(ny, nx, 0, 0, N, N) && B[ny][nx] == 'o') {
      B[ny][nx] = 'x';
      ny += dy[k], nx += dx[k];
    }
  }
  B[y][x] = 'x';
  return true;
}

bool isSameAB() {
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      if(A[i][j] != B[i][j]) return false;
  return true;
}

bool input() {
  cin >> N;
  assert(N <= 50);
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      cin >> A[i][j];

  for(int i = 0; i < N; i+=2)
    for(int j = 0; j < N; j+=2)
      if(A[i][j] == 'x') return false;

  return true;
}

map<Pi, vector<Pi>> tree;
bool buildTree(Pi s) {
  queue<Pi> que;
  que.push(s);
  set<Pi> st;
  st.insert(s);
  fill(B[0], B[MAX_N], 'o');
  while(!que.empty()) {
    Pi p = que.front(); que.pop();
    if(!fillB(p.first, p.second)) continue;
    for(Pi q : graph[p]) {
      if(st.count(q)) continue;
      tree[p].push_back(q);
      que.push(q);
      st.insert(q);
    }
  }
  return isSameAB();
}

vector<Pi> ans;
bool simulate(Pi s) {
  priority_queue<Pi, vector<Pi>, greater<Pi>> que;
  que.push(s);
  set<Pi> st;
  st.insert(s);
  fill(B[0], B[MAX_N], 'o');
  while(!que.empty()) {
    Pi p = que.top(); que.pop();
    if(!fillB(p.first, p.second)) continue;
    ans.push_back(p);
    for(Pi q : tree[p]) {
      if(st.count(q)) continue;
      que.push(q);
      st.insert(q);
    }
  }
  return isSameAB()&&!ans.empty();
}

int main() {
  if(!input()) {
    cout << -1 << endl;
    return 0;
  }

  Pi s = solve(0, 0, N, N);
  if(s.first == -1) {
    cout << 0 << endl;
    return 0;
  }
  if(s.first == -2) {
    cout << -1 << endl;
    return 0;
  }

  if(!buildTree(s)) {
    cout << -1 << endl;
    return 0;
  }

  if(!simulate(s)) {
    cout << -1 << endl;
    return 0;
  }

  cout << ans.size() << endl;
  for(Pi p : ans) {
    cout << p.first+1 << endl;
    cout << p.second+1 << endl;
  }

  return 0;
}
