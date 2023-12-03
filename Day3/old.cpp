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
  int N = grid.size();
  int M = grid[0].size();
  auto iss = [&](char c) {
    return !(('0' <= c && c <= '9') || c == '.');
  };
  auto valid = [&](int i, int j) -> bool {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  int ans = 0;
  F0R(i, N) {
    F0R(j, M) {
      if (j < M && isdigit(grid[i][j])) {
        int n = 0;
        int l = j;
        while (isdigit(grid[i][j])) {
          n = n * 10 + (grid[i][j] - '0');
          j++;
        }
        int r = j-1;

        bool p = false;
        for (int k = l-1; k <= r+1; k++) {
          p |= valid(i-1, k) && iss(grid[i-1][k]);
          p |= valid(i, k)   && iss(grid[i][k]);
          p |= valid(i+1, k) && iss(grid[i+1][k]);
        }
        if (p) ans += n;
      }
    }
  }
  cout << ans << '\n';
}
