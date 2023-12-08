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
  string S;
  cin >> S;

  string A, t, B, C;
  map<string, pair<string, string>> mp;

  while (cin >> A >> t >> B >> C) {
    mp[A] = {B, C};
  }

  vector<string> curs;
  for (auto [s, _]: mp) {
    if (s.back() == 'A') curs.push_back(s);
  }
  cout << sz(curs) << endl;
  cout << sz(mp) << endl;

  int end = 0;
  for (auto [s, _]: mp) {
    if (s.back() == 'Z') end++;
  }
  DEBUG(end);
  ll steps = 0;
  int i = 0;

  map<string, int> cyc;
  ll lc = 1;
  for (auto [s, _]: mp) {
    if (s.back() == 'A') {
      int len = 0;
      string cur = s;
      int i = 0;
      map<pair<string, int>, int> seen;
      while (true) {
        if (seen.count({cur, i})) break;
        seen[{cur, i}] = len;
        len++;
        cur = S[i] == 'L' ? mp[cur].first : mp[cur].second;
        i = (i + 1) % sz(S);
      }
      int off = seen[{cur, i}];
      int cyc = len - off;
      // cout << s << ": " << cyc << ": " << cur << ' ' << off << endl;
      int d = 0;
      while (true) {
        if (cur.back() == 'Z') break;
        d++;
        cur = S[i] == 'L' ? mp[cur].first : mp[cur].second;
        i = (i + 1) % sz(S);
      }
      // DEBUG(d);
      cout << cyc << ": " << d + off << endl;

      lc = std::lcm(lc, cyc);
    }
  }
  DEBUG(lc);
}
