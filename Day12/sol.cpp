#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define REP(n) for (int _=0; _<(n); _++)
#define F0R(i, a) for (int i=0; i<(a); i++)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
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

using VL = vector<ll>;
using VVL = vector<VL>;
using VVVL = vector<VVL>;

ll solve(string s, vector<int> v) {
  int max_len = *max_element(all(v));
  VVVL dp(sz(s), VVL(sz(v)+1, VL(max_len+1, -1)));

  return y_combinator([&](auto f, int i, int j, int cur) -> ll {
    // i = current index in s
    // j = current index in v
    // cur = length of current run
    if (i >= sz(s)) return j == sz(v);
    if (dp[i][j][cur] != -1) return dp[i][j][cur];
    auto& res = dp[i][j][cur];
    res = 0;
    // Case 1: place a . (reset cur)
    if ((s[i] == '.' || s[i] == '?') && cur == 0)
      res += f(i+1, j, 0);
    // Case 2: place a # (increment cur / increment j and reset cur)
    if ((s[i] == '#' || s[i] == '?') && j < sz(v)) {
      if (cur+1 == v[j])
        res += (i+1==sz(s) || s[i+1] != '#') * f(i+2, j+1, 0);
      else
        res += f(i+1, j, cur+1);
    }
    return res;
  })(0, 0, 0);
}

int main() {
  string line;

  string s, t;
  ll ans = 0;
  while (getline(cin, line)) {
    stringstream ss(line);
    getline(ss, s, ' ');
    vector<int> v;
    while (getline(ss, t, ',')) v.push_back(stoi(t));

    string S = s;
    REP(4) S += "?" + s;
    vector<int> V = v;
    REP(4) for (auto x: v) V.push_back(x);
    ans += solve(S, V);
  }
  cout << ans << '\n';
}
