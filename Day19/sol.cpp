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

using T = map<char, int>;
struct Ins {
  int ttype; // 0 = normal, 1 = default
  char c, comp;
  int x;
  string next;

  bool match(T cur) {
    if (ttype == 1) return true;
    else {
      if (comp == '<') {
        return cur[c] < x;
      }
      else {
        return cur[c] > x;
      }
    }
  }
};

struct Node {
  vector<Ins> v;
};

map<string, Node> MP;

using S = map<char, pair<int, int>>;
ll count(string node, S cur) {
  for (auto [_, p]: cur) {
    if (p.first > p.second) return 0;
  }
  if (node == "A") {
    ll ans = 1;
    for (auto [_, p]: cur) {
      ans *= 1LL * (p.second - p.first + 1);
    }
    return ans;
  }
  if (node == "R") return 0;

  ll ans = 0;
  for (const auto& ins: MP[node].v) {
    if (ins.ttype == 1) {
      ans += count(ins.next, cur);
    }
    else {
      if (ins.comp == '<') {
        S cur1 = cur;
        ckmin(cur1[ins.c].second, ins.x-1);
        S cur2 = cur;
        ckmax(cur2[ins.c].first, ins.x);
        ans += count(ins.next, cur1);
        cur = cur2;
      }
      else {
        S cur1 = cur;
        ckmin(cur1[ins.c].second, ins.x);
        S cur2 = cur;
        ckmax(cur2[ins.c].first, ins.x+1);
        ans += count(ins.next, cur2);
        cur = cur1;
      }
    }
  }
  return ans;
}

bool solve(string node, T cur) {
  if (node == "A") return true;
  if (node == "R") return false;
  for (auto ins: MP[node].v) {
    if (ins.match(cur)) {
      return solve(ins.next, cur);
    }
  }
  assert(0);
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line.empty()) break;
    stringstream ss(line);
    string name;
    getline(ss, name, ' ');
    string t;

    Node node;
    while (getline(ss, t, ',')) {
      if (sz(t) >= 2 && (t[1] == '<' || t[1] == '>')) {
        char c = t[0];
        char comp = t[1];
        int i = 2;
        while (isdigit(t[i])) i++;
        int x = stoi(t.substr(2, i - 2 + 1));
        string next = t.substr(i + 1);

        node.v.push_back({0, c, comp, x, next});
      }
      else {
        t = t.substr(0, sz(t) - 1);
        node.v.push_back({1, '#', '#', 0, t});
      }
    }
    MP[name] = node;
  }

  string init = "in";
  ll part1 = 0;
  while (getline(cin, line)) {
    stringstream ss(line);
    T cur;
    string t;
    while (getline(ss, t, ',')) {
      char c = t[0];
      int x = stoi(t.substr(2));
      cur[c] = x;
    }
    if (solve("in", cur)) {
      for (auto [_, x]: cur) {
        part1 += x;
      }
    }
  }
  DEBUG(part1);

  S cur = {
    {'x', {1, 4000}},
    {'m', {1, 4000}},
    {'a', {1, 4000}},
    {'s', {1, 4000}},
  };
  ll part2 = count("in", cur);
  DEBUG(part2);
}
