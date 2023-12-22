#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

using T = array<int, 3>;
using Brick = pair<T, T>;

int main() {
  string line;
  vector<Brick> bricks;
  int MX = 0;
  while (getline(cin, line)) {
    replace(all(line), '~', ' ');
    replace(all(line), ',', ' ');
    stringstream ss(line);
    Brick brick;
    string x;
    for (auto& y: brick.first) {
      ss >> y;
      ckmax(MX, y+1);
    }
    for (auto& y: brick.second) {
      ss >> y;
      ckmax(MX, y+1);
    }
    if (brick.first[2] > brick.second[2]) swap(brick.first, brick.second);
    bricks.push_back(brick);
  }
  int N = sz(bricks);
  vector<vector<int>> ht(MX, vector<int>(MX, 0));
  vector<vector<int>> id(MX, vector<int>(MX, -1));

  sort(all(bricks), [&](auto a, auto b) {
    return a.first[2] < b.first[2];
  });

  set<int> CANNOT;
  vector<vector<int>> adj(N);

  F0R(i, sz(bricks)) {
    auto [p1, p2] = bricks[i];
    auto [x1, y1, z1] = p1;
    auto [x2, y2, z2] = p2;
    int mx = 0;

    for (int x = min(x1, x2); x <= max(x1, x2); x++) {
      for (int y = min(y1, y2); y <= max(y1, y2); y++) {
        ckmax(mx, ht[x][y]);
      }
    }

    set<int> s;
    for (int x = min(x1, x2); x <= max(x1, x2); x++) {
      for (int y = min(y1, y2); y <= max(y1, y2); y++) {
        if (ht[x][y] == mx && id[x][y] != -1) {
          if (id[x][y] != -1) s.insert(id[x][y]);
        }
        ht[x][y] = mx + (z2 - z1 + 1);
        id[x][y] = i;
      }
    }
    if (s.size() == 1) {
      CANNOT.insert(*s.begin());
    }

    for (auto j: s) adj[j].push_back(i);
  }

  int part1 = N - sz(CANNOT);
  cout << "Part 1: " << part1 << endl;

  int part2 = 0;
  F0R(i, N) {
    vector<int> indegree(N, 0);
    F0R(j, N) for (auto k: adj[j]) indegree[k]++;
    queue<int> q;
    q.push(i);
    while (!q.empty()) {
      int x = q.front(); q.pop();
      if (x != i) part2++;
      for (auto y: adj[x]) {
        if (--indegree[y] == 0) {
          q.push(y);
        }
      }
    }
  }
  cout << "Part 2: " << part2 << endl;
}
