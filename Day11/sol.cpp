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

  vector<int> row(N);
  F0R(i, N) {
    bool poss = true;
    F0R(j, M) {
      if (grid[i][j] == '#') poss = false;
    }
    if (poss) row[i] = true;
  }

  FOR(i, 1, N) row[i] += row[i-1];

  vector<int> col(M);
  F0R(j, M) {
    bool poss = true;
    F0R(i, sz(grid)) {
      if (grid[i][j] == '#') poss = false;
    }
    if (poss) col[j] = true;
  }

  FOR(i, 1, M) col[i] += col[i-1];

  vector<pair<int, int>> v;
  F0R(i, N) {
    F0R(j, M) {
      if (grid[i][j] == '#') {
        v.push_back({i, j});
      }
    }
  }

  const int D = 1000000;
  auto xd = [&](int l, int r) -> ll {
    if (l > r) swap(l, r);
    return (r - l) + (D - 1) * (row[r] - (l == 0 ? 0 : row[l-1]));
  };
  auto yd = [&](int l, int r) -> ll {
    if (l > r) swap(l, r);
    return (r - l) + (D - 1) * (col[r] - (l == 0 ? 0 : col[l-1]));
  };

  ll ans = 0;
  F0R(i, sz(v)) {
    FOR(j, i+1, sz(v)) {
      ans += xd(v[i].first, v[j].first) + yd(v[i].second, v[j].second);
    }
  }
  cout << ans << '\n';
}
