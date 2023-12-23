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

/*
** Directed graph of start, end, and all slopes
** Longest path in this graph (DAG)
** Need to find edges and weights
 */

int main() {
  string line;
  vector<string> grid;
  while (cin >> line) {
    grid.push_back(line);
  }
  int N = grid.size(), M = grid[0].size();

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  string SLOPES = "<>v^"; // NO ^ actually
  auto isSlope = [&](char c) {
    auto t = SLOPES.find(c);
    return t != string::npos;
  };

  map<char, pair<int, int>> SLOPE_MP = {
    {'<', {0, -1}},
    {'>', {0, +1}},
    {'v', {+1, 0}},
    {'^', {-1, 0}},
  };

  auto add = [&](pair<int, int> a, pair<int, int> b) -> pair<int, int> {
    return {a.first + b.first, a.second + b.second};
  };

  vector<pair<int,int>> vec;
  F0R(i, N) {
    F0R(j, M) {
      if (i == 0 && grid[i][j] == '.') vec.push_back({i, j});
      if (i == N-1 && grid[i][j] == '.') vec.push_back({i, j});
      if (isSlope(grid[i][j])) vec.push_back({i, j});
    }
  }
  map<pair<int, int>, int> compress;
  F0R(i, sz(vec)) compress[vec[i]] = i;
  int n = sz(vec);

  auto valid = [&](int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  vector<vector<pair<int, int>>> adj(n);
  vector<int> indegree(n);

  auto dfs = y_combinator([&](auto dfs, int oi, int oj, int i, int j, int pi, int pj, int d) -> void {
    F0R(k, 4) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (make_pair(ni, nj) == make_pair(pi, pj)) continue;
      if (valid(ni, nj) &&
          ((isSlope(grid[ni][nj]) && add({ni, nj}, SLOPE_MP[grid[ni][nj]]) != make_pair(i, j)) || make_pair(ni, nj) == vec[n-1])) {
        int id1 = compress[{oi, oj}];
        int id = compress[{ni, nj}];
        indegree[id]++;
        cout << id1 << ' ' << id << ": " << d+1 << endl;
        adj[id1].emplace_back(id, d+1);
      }
    }

    F0R(k, 4) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (make_pair(ni, nj) == make_pair(pi, pj)) continue;
      if (valid(ni, nj) && grid[ni][nj] == '.') {
        dfs(oi, oj, ni, nj, i, j, d+1);
      }
    }
  });

  for (auto [oi, oj]: vec) {
    dfs(oi, oj, oi + SLOPE_MP[grid[oi][oj]].first, oj + SLOPE_MP[grid[oi][oj]].second, oi, oj, 1);
  }

  // TOP sort
  vector<int> dist(n);
  queue<int> q;
  q.push(0);
  int C = 0;
  while (!q.empty()) {
    C++;
    int i = q.front(); q.pop();
    for (auto [j, w]: adj[i]) {
      ckmax(dist[j], dist[i] + w);
      if (--indegree[j] == 0) q.push(j);
    }
  }

  cout << dist[n-1] << endl;
  DEBUG(C);
  DEBUG(n);

}
