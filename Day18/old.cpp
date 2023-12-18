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
  char DIR;
  int X;
  string HEX;
  int MX = 800;
  vector<string> G(MX, string(MX, '.'));
  map<char, pair<int, int>> mp = {
  {'U', {-1, 0}},
  {'D', {1, 0}},
  {'L', {0, -1}},
  {'R', {0, 1}},
};


  int x = 400, y = 400;
  while (cin >> DIR >> X >> HEX) {
    int nx = x + X * mp[DIR].first;
    int ny = y + X * mp[DIR].second;

    for (int i = min(x, nx); i <= max(x, nx); i++) {
      for (int j = min(y, ny); j <= max(y, ny); j++) {
        G[i][j] = '#';
      }
    }
    // cout << x << ' ' << y << endl;
    assert(x >= 0 && y >= 0);
    assert(x < MX && y < MX);

    x = nx, y = ny;
  }

  vector<vector<bool>> vis(MX, vector<bool>(MX));
  auto valid = [&](int i, int j) {
    return 0 <= i && i < MX && 0 <= j && j < MX;
  };
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};


  int ans = 0;
  F0R(i, MX) {
    F0R(j, MX) {
      if (G[i][j] == '#') ans++;
    }
  }
  F0R(i, MX) {
    F0R(j, MX) {
      if (!vis[i][j] && G[i][j] == '.') {
        vector<pair<int, int>> v;
        bool border = false;
        auto dfs = y_combinator([&](auto dfs, int i, int j) -> void {
          if (!vis[i][j]) {
            vis[i][j] = 1;
            v.push_back({i, j});
            F0R(k, 4) {
              int ni = i + dx[k];
              int nj = j + dy[k];
              if (!valid(ni, nj)) {
                border = true;
              }
              else {
                if (G[ni][nj] == '.') dfs(ni, nj);
              }
            }
          }
        });
        dfs(i, j);
        if (!border) {
          cout << "AT " << i << ' ' << j << endl;
          // assume all 1 region
          for (auto [x, y]: v) {
            bool take = true;
            F0R(k, 4) {
              int nx = x + dx[k];
              int ny = y + dy[k];
              if (G[nx][ny] == '#') take = false;
            }
            if (!take) {
              G[x][y] = '#';
              ans++;
            }
            // if (take) ans++;
          }
        }
      }
    }
  }
  DEBUG(ans);
  for (auto s: G) {
    // cout << s << endl;
  }
  int c = 0;
  F0R(i, MX) {
    F0R(j, MX) {
      if (G[i][j] == '#') c++;
    }
  }
  DEBUG(c);
}
