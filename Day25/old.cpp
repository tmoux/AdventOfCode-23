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

using vi = vector<int>;
using pii = pair<int, int>;

int b1, b2;
int bridge_id = -1;
namespace BC {
  vi num, st;
  vector<vector<pii>> ed;
  vector<pii> edges, bridges;
  int Time;
  template<class F>
  int dfs(int at, int par, F& f) {
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (e == b1 || e == b2) continue;
        if (num[y]) {
          top = min(top, num[y]);
          if (num[y] < me)
            st.push_back(e);
        } else {
          int si = sz(st);
          int up = dfs(y, e, f);
          top = min(top, up);
          if (up == me) { // BCC (list of edges)
            st.push_back(e);
            f(vi(st.begin() + si, st.end()));
            st.resize(si);
          }
          else if (up < me) st.push_back(e);
          else { // BRIDGE
            cout << "BRIDGE" << endl;
            // auto [a, b] = edges[e];
            // bridges.emplace_back(a, b);
            bridge_id = e;
          }
        }
      }
    return top;
  }

  template<class F>
  void bicomps(F f) {
    num.assign(sz(ed), 0);
    FOR(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
  }
} using namespace BC;

int main() {
  ed.resize(1600);
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
      ed[compress[s]].emplace_back(compress[t], e);
      ed[compress[t]].emplace_back(compress[s], e);
      e++;
    }
  }

  // DEBUG(sz(compress));
  // return 0;

  FOR(e1, 0, e) {
    FOR(e2, e1+1, e) {
      cout << e1 << ' ' << e2 << endl;
      b1 = e1;
      b2 = e2;
      bicomps([&](auto f) {});
      if (bridge_id != -1) {
        cout << "FOUND " << bridge_id << ' ' << e1 << ' ' << e2 << endl;
        int N = sz(compress);
        vector<bool> vis(N, false);
        auto dfs = y_combinator([&](auto dfs, int i, int& c) -> void {
          if (!vis[i]) {
            vis[i] = 1;
            c++;
            for (auto [j, e]: ed[i]) {
              if (e == b1 || e == b2 || e == bridge_id) continue;
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
            cout << "comp size " << c << endl;
          }
        }
        DEBUG(ans);
        return 0;
      }
    }
  }
}
