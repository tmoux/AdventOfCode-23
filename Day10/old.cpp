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
  pair<int, int> S;
  F0R(i, N) {
    F0R(j, M) {
      if (grid[i][j] == 'S') {
        S = {i, j};
      }
    }
  }

  vector<vector<int>> dist(N, vector<int>(M, 1e9));
  dist[S.first][S.second] = 0;
  queue<pair<int, int>> q; q.push(S);

  auto valid = [&](int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};

  auto checkCur = [&](int k, char c) -> bool {
    if (k == 0) {
      return c == '-' || c == 'L' || c == 'F';
    }
    else if (k == 1) {
      return c == 'S' || c == '|' || c == 'F' || c == '7';
    }
    else if (k == 2) {
      return c == '-' || c == 'J' || c == '7';
    }
    else if (k == 3) {
      return c == 'S' || c == '|' || c == 'J' || c == 'L';
    }
    else assert(false);
  };

  auto check = [&](int k, char c) -> bool {
    if (k == 0) {
      return c == '-' || c == 'J' || c == '7';
    }
    else if (k == 1) {
      return c == '|' || c == 'J' || c == 'L';
    }
    else if (k == 2) {
      return c == '-' || c == 'L' || c == 'F';
    }
    else if (k == 3) {
      return c == '|' || c == 'F' || c == '7';
    }
    else assert(false);
  };

  int ans = 0;
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    cout << i << ' ' << j << endl;
    ckmax(ans, dist[i][j]);
    F0R(k, 4) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (valid(ni, nj) && checkCur(k, grid[i][j]) && check(k, grid[ni][nj]) && dist[ni][nj] > dist[i][j] + 1) {
        dist[ni][nj] = dist[i][j] + 1;
        q.push({ni, nj});
      }
    }
  }
  cout << ans << '\n';
}
