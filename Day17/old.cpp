#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};


int main() {
  string line;
  vector<string> grid;
  while (cin >> line) {
    grid.push_back(line);
  }
  int N = grid.size(), M = grid[0].size();

  using VI = vector<int>;
  using VVI = vector<VI>;
  using VVVI = vector<VVI>;
  using VVVVI = vector<VVVI>;

  auto dijkstra = [&]() -> VVVVI {
    const int INF = 2e9;
    VVVVI dist(N, VVVI(N, VVI(4, VI(4, INF))));

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
      int d1 = (d + 3) % 4;
      ret.push_back({x + dx[d1], y + dy[d1], d1, 1});
      int d2 = (d + 1) % 4;
      ret.push_back({x + dx[d2], y + dy[d2], d2, 1});
      if (s < 3)
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
        // if (dist[v] > dist[u] + weight) {
        //   dist[v] = dist[u] + weight;
        //   pq.push({dist[v], v});
        // }
      }
    }
    return dist;
  };

  auto dist = dijkstra();
  int ans = 2e9;
  F0R(d, 4) {
    F0R(s, 4) {
      ckmin(ans, dist[N-1][M-1][d][s]);

    }
  }
  cout << ans << endl;
}
