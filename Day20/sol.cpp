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

  map<string, vector<string>> adj, radj;
  map<string, char> ttype;
  while (getline(cin, line)) {
    stringstream ss(line);
    string node;
    vector<string> v;
    string t;
    ss >> node;
    ss >> t;
    while (ss >> t) {
      if (t.back() == ',') t.pop_back();
      v.push_back(t);
    }

    if (node != "broadcaster") {
      char c = node[0];
      node = node.substr(1);
      ttype[node] = c;
    }
    adj[node] = v;
    for (auto s: v) radj[s].push_back(node);
  }

  map<string, bool> on;
  map<string, map<string, bool>> last;

  auto reset = [&]() -> void {
    on.clear();
    last.clear();
  };

  bool x_on = false;
  string target;
  auto push = [&]() -> pair<int, int> {
    int low = 0, high = 0;
    queue<tuple<string, string, int>> q;
    q.emplace("broadcaster", "", 0);
    while (!q.empty()) {
      auto [s, p, pulse] = q.front(); q.pop();
      last[p][s] = pulse;
      (pulse == 0 ? low : high)++;
      if (s == "broadcaster") {
        for (auto t: adj[s]) {
          q.emplace(t, s, pulse);
        }
      }
      else if (ttype[s] == '%') {
        if (pulse == 0) {
          on[s] = !on[s];
          for (auto t: adj[s]) {
            q.emplace(t, s, on[s]);
          }
        }
      }
      else if (ttype[s] == '&') {
        bool all_high = true;
        for (auto t: radj[s]) {
          if (!last[t][s]) all_high = false;
        }
        if (!all_high && s == target) x_on = true;
        if (all_high) {
          for (auto t: adj[s]) {
            q.emplace(t, s, !all_high);
          }
        }
      }
    }
    return {low, high};
  };

  // Part 1
  {
    int low = 0, high = 0;
    REP(1000) {
      auto [x, y] = push();
      low += x;
      high += y;
    }
    cout << "part 1: " << (low * high) << endl;
  }

  // Part 2
  set<string> V = {"lk", "zv", "sp", "xt"}; // Manual inspection!

  map<string, vector<int>> times;

  ll ans = 1;
  for (auto s: V) {
    reset();
    target = s;
    x_on = 0;
    int iter = 0;
    int t = -1;
    while (true) {
      x_on = false;
      iter++;
      push();
      if (x_on) {
        if (t == -1) t = iter;
        else {
          ans = std::lcm(ans, iter - t);
          break;
        }
      }
    }
  }
  cout << "part 2: " << ans << '\n';

  for (auto [s, v]: adj) {
    for (auto t: v) {
      cout << s << ' ' << t << endl;
    }
  }
}
