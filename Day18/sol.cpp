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
  map<char, pair<int, int>> mp = {
    {'U', {-1, 0}},
    {'D', {1, 0}},
    {'L', {0, -1}},
    {'R', {0, 1}},
  };

  auto tohex = [&](char c) {
    if (0 <= c && c <= '9') return c - '0';
    else return c - 'a' + 10;
  };

  // Assume on RHS?
  char chars[] = {'R', 'D', 'L', 'U'};

  vector<int> dirs;

  vector<pair<int, int>> ins;
  vector<pair<ll, ll>> v;
  int cx = 0, cy = 0;
  ll perim = 0;
  while (cin >> DIR >> X >> HEX) {
    string t = HEX.substr(2, sz(HEX) - 3);
    int x = 0;
    F0R(i, 5) {
      x = (x * 16) + tohex(t[i]);
    }
    int d = t.back() - '0';

    // OLD
    // x = X;
    // if (DIR == 'R') d = 0;
    // if (DIR == 'D') d = 1;
    // if (DIR == 'L') d = 2;
    // if (DIR == 'U') d = 3;

    char dir = chars[d];
    cx += x * mp[dir].first;
    cy += x * mp[dir].second;
    v.push_back({cx, cy});

    perim += x;
  }

  ll ans = 0;
  F0R(i, sz(v)) {
    ll y = v[i].second;
    ll x = v[(i+1)%sz(v)].first - v[(i-1+sz(v))%sz(v)].first;
    ans += y * x;
  }
  ans /= 2;
  ans += perim / 2 + 1;
  DEBUG(ans);
}
