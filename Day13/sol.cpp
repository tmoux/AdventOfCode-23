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

int solve(vector<string> g, int p) {
  int N = g.size(), M = g[0].size();
  F0R(i, N-1) {
    if (i+1 == p) continue;
    bool poss = true;
    for (int r = 0; r <= i; r++) {
      int nr = i + 1 + (i - r);
      F0R(j, M) {
        if (nr < N && g[r][j] != g[nr][j]) {
          poss = false;
          break;
        }
      }
    }
    if (poss) return i+1;
  }
  return 0;
}

pair<int, int> F(vector<string> g, pair<int, int> p = {-1, -1}) {
  int N = g.size(), M = g[0].size();
  vector<string> gt(M, string(N, '.'));
  F0R(i, N) F0R(j, M) gt[j][i] = g[i][j];

  return {solve(g, p.first), solve(gt, p.second)};
}

int main() {
  string line;
  vector<string> g;

  ll ans = 0;
  while (getline(cin, line)) {
    if (line.empty()) {
      auto [A, B] = F(g);
      int N = g.size(), M = g[0].size();

      bool h = false;
      F0R(i, N) {
        F0R(j, M) {
          g[i][j] = g[i][j] == '#' ? '.' : '#';
          auto [a, b] = F(g, {A, B});
          cout << i << ' ' << j << ": " << A << ' ' << B << " -- " << a << ' ' << b << endl;
          if (a > 0 && a != A) {
            ans += 100 * a;
            cout << A << ' ' << B << ' ' << a << ' ' << b << endl;
            h = true;
            goto done;
          }
          else if (b > 0 && b != B) {
            ans += b;
            cout << A << ' ' << B << ' ' << a << ' ' << b << endl;
            h = true;
            goto done;
          }
          g[i][j] = g[i][j] == '#' ? '.' : '#';
        }
      }
      done:;
      assert(h);

      g.clear();
    }
    else g.push_back(line);
  }
  cout << ans << '\n';
}
