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
  getline(cin, line);
  string t;
  vector<ll> seeds;
  {
    stringstream ss(line.substr(7));
    while (getline(ss, t, ' ')) {
      // cout << t << endl;
      seeds.push_back(stoll(t));
    }
  }
  DEBUG(seeds);
  getline(cin, line);


  using P = pair<ll, ll>;
  using T = vector<pair<P, P>>;
  vector<T> V;
  REP(7) {
    getline(cin, line);

    T cur;
    while (true) {
      getline(cin, line);
      if (line.empty()) break;
      else {
        stringstream ss(line);
        ll x, y, d; ss >> x >> y >> d;
        cur.push_back({{y, y + d - 1}, {x, x + d - 1}});
      }
    }
    V.push_back(cur);
  }

  cout << V << endl;

  auto get_pos = [&](ll x) {
    cout << x << ": " << endl;
    for (auto v: V) {
      ll nxt = -1;
      for (auto [p1, p2]: v) {
        auto [a, b] = p1;
        auto [c, d] = p2;
        if (a <= x && x <= b) {
          nxt = c + (x - a);
          break;
        }
      }
      if (nxt == -1) nxt = x;
      x = nxt;
      cout << "now " << x << endl;
    }
    return x;
  };


  ll ans = 1e18;
  for (auto x: seeds) {
    // cout << x << ": " << get_pos(x) << endl;
    ckmin(ans, get_pos(x));
  }
  cout << ans << endl;
}
