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

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

using vi = vector<int>;
using pii = pair<int, int>;
vector<vector<pair<int, int>>> adj;
array<int, 2> edges[5000];
int N, M;

vector<int> karger() {
  DSU dsu(N);
  auto distinct = [&](int e) {
    return dsu.Find(edges[e][0]) != dsu.Find(edges[e][1]);
  };

  auto getE = [&]() -> int {
    vector<int> v;
    F0R(i, M) if (distinct(i)) v.push_back(i);
    return v[rng()%sz(v)];
  };
  int n = N;
  while (n > 2) {
    int e = getE();
    n--;
    auto [a, b] = edges[e];
    dsu.Union(a, b);
  }
  vector<int> ans;
  F0R(i, M) {
    if (distinct(i)) ans.push_back(i);
  }
  return ans;
}

vector<int> mincut() {
  vector<int> ans;
  while (ans.empty() || sz(ans) > 3) {
    auto v = karger();
    if (ans.empty() || sz(v) < sz(ans)) ans = v;
  }
  return ans;
}

int main() {
  adj.resize(1600);
  string line;
  map<string, int> compress;
  int pt = 0;
  int e = 0;
  while (getline(cin, line)) {
    stringstream ss(line);
    string s, t;
    ss >> s;
    s.pop_back();
    if (!compress.count(s)) compress[s] = pt++;
    while (ss >> t) {
      if (!compress.count(t)) compress[t] = pt++;
      edges[e] = {compress[s], compress[t]};
      adj[compress[s]].emplace_back(compress[t], e);
      adj[compress[t]].emplace_back(compress[s], e);
      e++;
    }
  }
  N = sz(compress);
  M = e;

  auto v = mincut();
  assert(sz(v) == 3);

  vector<bool> vis(N, false);
  auto dfs = y_combinator([&](auto dfs, int i, int& c) -> void {
    if (!vis[i]) {
      vis[i] = 1;
      c++;
      for (auto [j, e]: adj[i]) {
        if (e == v[0] || e == v[1] || e == v[2]) continue;
        dfs(j, c);
      }
    }
  });
  int ans = 1;
  F0R(i, N) {
    if (!vis[i]) {
      int c = 0;
      dfs(i, c);
      ans *= c;
    }
  }
  cout << ans << endl;
}
