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
  int sum = 0;

  auto isdigit = [&](char c) {
    return '0' <= c && c <= '9';
  };

  map<string, int> mp = {
  {"one", 1},
  {"two", 2},
  {"three", 3},
  {"four", 4},
  {"five", 5},
  {"six", 6},
  {"seven", 7},
  {"eight", 8},
  {"nine", 9}
  };
  while (cin >> line) {
    int a, b;

    for (int i = 0; i < sz(line); i++) {
      if (isdigit(line[i])) {
        a = line[i] - '0';
        break;
      }
      for (int j = 1; j <= 5; j++) {
        if (i + j <= sz(line)) {
          string s = line.substr(i, j);
          if (mp.count(s)) {
            a = mp[s];
            goto done;
          }
        }
      }
    }
    done:;
    for (int i = sz(line)-1; i >= 0; i--) {
      if (isdigit(line[i])) {
        b = line[i] - '0';
        break;
      }
      for (int j = 1; j <= 5; j++) {
        if (i + j <= sz(line)) {
          string s = line.substr(i, j);
          if (mp.count(s)) {
            b = mp[s];
            goto doneb;
          }
        }
      }
    }
    doneb:;

    sum += a * 10 + b;
  }
  cout << sum << '\n';
}
