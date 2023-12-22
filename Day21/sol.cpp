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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int K = 26501365;
  string line;
  vector<string> grid;
  while (cin >> line) {
    grid.push_back(line);
  }
  vector<string> orig = grid;
  int N = grid.size(), M = grid[0].size();
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  vector<int> numDist(N+1); // # that are at least this far away and same parity
  int L = K / N - 1;
  numDist[0] = 1;
  for (int d = 1; d <= N; d++) {
    vector<string> ngrid(N, string(M, '.'));
    F0R(i, N) {
      F0R(j, M) if (grid[i][j] == '#') ngrid[i][j] = '#';
    }
    F0R(i, N) {
      F0R(j, M) {
        if (grid[i][j] == 'S') {
          F0R(k, 4) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (0 <= ni && ni < N && 0 <= nj && nj < M && grid[ni][nj] != '#') {
              ngrid[ni][nj] = 'S';
            }
          }
        }
      }
    }
    grid = ngrid;
    F0R(i, N) {
      F0R(j, N) {
        if (grid[i][j] == 'S') numDist[d]++;
      }
    }
  }

  // 3x3 grid of NxN
  auto countTypes = [&](vector<array<int, 3>> init, int par = 0) -> int {
    par ^= 1;
    int px = -1, py = -1;
    F0R(i, N) {
      F0R(j, N) {
        if (orig[i][j] == 'S') {
          px = i, py = j;
        }
      }
    }
    assert(px != -1 && py != -1);
    vector<string> G(3*N, string(3*N, '.'));
    F0R(i, N) {
      F0R(j, N) {
        F0R(x, 3) {
          F0R(y, 3) {
            G[i + N * x][j + N * y] = orig[i][j];
          }
        }
      }
    }

    queue<pair<int, int>> q;
    vector<vector<int>> dist(3*N, vector<int>(3*N, -1));
    for (auto [x, y, d]: init) {
      q.push({px + N*x, py + N*y});
      dist[px + N*x][py + N*y] = d;
    }

    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      int d = dist[i][j];
      if (d > 0) {
        F0R(k, 4) {
          int ni = i + dx[k];
          int nj = j + dy[k];
          if (0 <= ni && ni < 3*N && 0 <= nj && nj < 3*N && G[ni][nj] != '#' && dist[ni][nj] < dist[i][j] - 1) {
            dist[ni][nj] = dist[i][j] - 1;
            q.push({ni, nj});
          }
        }
      }
    }
    int ans = 0;
    F0R(i, N) {
      F0R(j, N) {
        int op = (px + N + py + N) % 2;
        int p = (i + j) % 2;
        if (dist[i+N][j+N] > -1 && ((p == op) ^ par)) ans++;
      }
    }
    return ans;
  };
  // 0 = from Up
  // 1 = from Down
  // 2 = from Right
  // 3 = from Left
  // 4 = from UL
  // 5 = from UR
  // 6 = from DL
  // 7 = from DR
  vector<int> numType(8);
  int D1 = K - max(0, (L - 0) * N);
  int D2 = K - max(0, (L - 1) * N);

  numType[0] = countTypes({{0, 1, D1}});
  numType[1] = countTypes({{2, 1, D1}});
  numType[2] = countTypes({{1, 2, D1}});
  numType[3] = countTypes({{1, 0, D1}});
  numType[4] = countTypes({{0, 0, D2}, {1, 0, D1}, {0, 1, D1}});
  numType[5] = countTypes({{0, 2, D2}, {1, 2, D1}, {0, 1, D1}});
  numType[6] = countTypes({{2, 0, D2}, {1, 0, D1}, {2, 1, D1}});
  numType[7] = countTypes({{2, 2, D2}, {2, 1, D1}, {1, 2, D1}});
  numType[8] = countTypes({{0, 0, D1}}, 1);
  numType[9] = countTypes({{0, 2, D1}}, 1);
  numType[10] = countTypes({{2, 0, D1}}, 1);
  numType[11] = countTypes({{2, 2, D1}}, 1);

  ll ans = 0;
  for (int y = -L; y <= L; y++) {
    int x = 2 * (L - abs(y) + 1) - 1;
    if (x > 0) {
      int a = x / 2;
      int b = x - a;
      ans += 1LL * a * numDist[N] + 1LL * b * numDist[N-1];
    }
    if (y == -L) ans += numType[0];
    if (y == L) ans += numType[1];
    if (y == 0) ans += numType[2] + numType[3];
    if (y < 0) ans += numType[4] + numType[5];
    if (y > 0) ans += numType[6] + numType[7];
  }
  ans += 1LL * (L + 1) * (numType[8] + numType[9] + numType[10] + numType[11]);
  cout << ans << '\n';
}
