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
  string line;
  vector<string> grid;
  while (cin >> line) {
    grid.push_back(line);
  }
  int N = grid.size();
  int M = grid[0].size();

  vector<bool> row(N);
  F0R(i, N) {
    bool poss = true;
    F0R(j, M) {
      if (grid[i][j] == '#') poss = false;
    }
    if (poss) row[i] = true;
  }

  F0Rd(i, N) {
    if (row[i]) {
      grid.insert(grid.begin() + i, string(M, '.'));
    }
  }

  vector<bool> col(M);
  F0R(j, M) {
    bool poss = true;
    F0R(i, sz(grid)) {
      if (grid[i][j] == '#') poss = false;
    }
    if (poss) col[j] = true;
  }

  F0Rd(j, M) {
    if (col[j]) {
      F0R(i, sz(grid)) {
        grid[i].insert(grid[i].begin() + j, '.');
      }
    }
  }

  N = grid.size();
  M = grid[0].size();

  vector<pair<int, int>> v;
  F0R(i, N) {
    F0R(j, M) {
      if (grid[i][j] == '#') {
        v.push_back({i, j});
      }
    }
  }

  F0R(i, N) {
    F0R(j, M) {
      cout << grid[i][j];
    }
    cout << endl;
  }

  ll ans = 0;
  F0R(i, sz(v)) {
    FOR(j, i+1, sz(v)) {
      ans += abs(v[i].first - v[j].first) + abs(v[i].second - v[j].second);
    }
  }
  cout << ans << '\n';

  // ll ans = 0;
  // for (auto [x, y]: v) {
  //   vector<vector<int>> dist(N, vector<int>(M, 1e9));
  //   queue<pair<int, int>> q;
  //   dist[x][y] = 0;
  //   q.push({x, y});
  //   const int dx[] = {0, 1, 0, -1};
  //   const int dy[] = {1, 0, -1, 0};


  //   while (!q.empty()) {
  //     auto [i, j] = q.front(); q.pop();
  //     if (grid[i][j] == '#') ans += dist[i][j];
  //     F0R(k, 4) {
  //       int ni = i + dx[k];
  //       int nj = j + dy[k];
  //       if (0 <= ni && ni < N && 0 <= nj && nj < M) {
  //         if (dist[ni][nj] > dist[i][j] + 1) {
  //           dist[ni][nj] = dist[i][j] + 1;
  //           q.push({ni, nj});
  //         }
  //       }
  //     }
  //   }
  // }
  // cout << ans / 2 << '\n';
}
