#include <bits/stdc++.h>
using namespace std;

#define F0R(i, a) for (int i=0; i<(a); i++)
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;
using VVVVI = vector<VVVI>;

int main() {
  string line;
  vector<string> grid;
  while (cin >> line) grid.push_back(line);
  int N = grid.size(), M = grid[0].size();

  auto dijkstra = [&]() -> VVVVI {
    const int INF = 2e9;
    VVVVI dist(N, VVVI(M, VVI(4, VI(11, INF))));

    using T = array<int, 4>;
    priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
    F0R(d, 4) {
      dist[0][0][d][0] = 0;
      pq.push({0, {0, 0, d, 0}});
    }

    auto valid = [&](int x, int y) {
      return 0 <= x && x < N && 0 <= y && y < M;
    };

    auto getAdj = [&](int x, int y, int d, int s) -> vector<T> {
      vector<T> ret;
      if (s >= 4) {
        int d1 = (d + 3) % 4;
        ret.push_back({x + dx[d1], y + dy[d1], d1, 1});
      }
      if (s >= 4) {
        int d2 = (d + 1) % 4;
        ret.push_back({x + dx[d2], y + dy[d2], d2, 1});
      }
      if (s < 10)
        ret.push_back({x + dx[d], y + dy[d], d, s + 1});

      return ret;
    };

    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      auto [x, y, dir, s] = u;
      if (d > dist[x][y][dir][s]) continue;
      for (auto [nx, ny, nd, ns]: getAdj(x, y, dir, s)) {
        if (!valid(nx, ny)) continue;
        int weight = grid[nx][ny] - '0';
        if (dist[nx][ny][nd][ns] > dist[x][y][dir][s] + weight) {
          dist[nx][ny][nd][ns] = dist[x][y][dir][s] + weight;
          pq.push({dist[nx][ny][nd][ns], {nx, ny, nd, ns}});
        }
      }
    }
    return dist;
  };

  auto dist = dijkstra();
  int ans = 2e9;
  F0R(d, 4) {
    for (int s = 4; s <= 10; s++) {
      ckmin(ans, dist[N-1][M-1][d][s]);
    }
  }
  cout << ans << endl;
}
