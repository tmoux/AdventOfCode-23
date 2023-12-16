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
  vector<string> grid;
  string line;
  while (cin >> line) {
    grid.push_back(line);
  }
  int N = grid.size(), M = grid[0].size();

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};
  // right is 0

  auto valid = [&](int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  using T = array<int, 3>;

  auto check = [&](int x, int y, int init_d) -> int {
    vector<vector<vector<bool>>> vis(N, vector<vector<bool>>(M, vector<bool>(4, false)));
    queue<T> q;
    q.push({x, y, init_d});
    while (!q.empty()) {
      auto [i, j, d] = q.front(); q.pop();
      if (!valid(i, j)) continue;
      if (!vis[i][j][d]) {
        vis[i][j][d] = 1;

        if ((d == 0 || d == 2) && grid[i][j] == '|') {
          q.push({i-1, j, 3});
          q.push({i+1, j, 1});
        }
        else if ((d == 1 || d == 3) && grid[i][j] == '-') {
          q.push({i, j-1, 2});
          q.push({i, j+1, 0});
        }
        else {
          int nd = d;
          if (grid[i][j] == '/') {
            if (d == 0) nd = 3;
            else if (d == 3) nd = 0;
            else if (d == 1) nd = 2;
            else nd = 1;
          }
          else if (grid[i][j] == '\\') {
            if (d == 0) nd = 1;
            else if (d == 1) nd = 0;
            else if (d == 2) nd = 3;
            else nd = 2;
          }
          int ni = i + dx[nd];
          int nj = j + dy[nd];
          q.push({ni, nj, nd});
        }
      }
    }
    int ans = 0;
    F0R(i, N) {
      F0R(j, M) {
        bool p = false;
        F0R(k, 4) if (vis[i][j][k]) p = true;
        if (p) ans++;
      }
    }
    return ans;
  };


  int ans = 0;
  F0R(i, N) {
    F0R(j, M) {
      if (i == 0 || i == N-1 || j == 0 || j == M-1) {
        F0R(d, 4) {
          ckmax(ans, check(i, j, d));
        }
      }
    }
  }
  cout << ans << endl;
  // Guess: don't actually have to check directions:
}
