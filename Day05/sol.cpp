#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define REP(n) for (int _=0; _<(n); _++)
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

int main() {
  // Parse input
  string line;
  getline(cin, line);
  string t;
  vector<pair<ll, ll>> curRanges;
  {
    stringstream ss(line);
    ss >> t;
    vector<ll> v;
    ll x;
    while (ss >> x) v.push_back(x);
    for (int i = 0; i < sz(v); i += 2) {
      curRanges.push_back({v[i], v[i]+v[i+1] - 1});
    }
  }
  getline(cin, line);

  using P = pair<ll, ll>;
  using T = pair<P, P>;
  vector<vector<T>> V;
  REP(7) {
    getline(cin, line);
    vector<T> cur;
    while (getline(cin, line) && !line.empty()) {
      stringstream ss(line);
      ll x, y, d; ss >> x >> y >> d;
      cur.push_back({{y, y + d - 1}, {x, x + d - 1}});
    }
    sort(all(cur));
    V.push_back(cur);
  }
  ///////////////////////////////////////////////////////////////////////
  const ll MAX = 1e18;
  for (auto v: V) {
    auto next_interval = [&](ll l) -> pair<P, P> {
      // Find the interval [X, Y] that contains l (if one exists).
      // Otherwise, return the nearest interval to the right (or infinity if none exists)
      auto it = std::lower_bound(all(v), pair<P, P>({{l+1, 0}, {0, 0}}));
      if (it != v.begin() && l <= prev(it)->first.second) return *prev(it);
      else if (it != v.end()) return *it;
      else return {{MAX, MAX}, {MAX, MAX}};
    };
    vector<pair<ll, ll>> nxtRanges;
    for (auto [l, r]: curRanges) {
      // Split up the range [l, r] into new ranges
      ll cur = l;
      while (cur <= r) {
        auto [p1, p2] = next_interval(cur);
        auto [X1, Y1] = p1;
        auto [X2, Y2] = p2;

        if (X1 > r) {
          nxtRanges.push_back({cur, r});
          cur = r + 1;
        }
        else if (X1 <= cur && cur <= Y1) {
          ll R = min(r, Y1);
          nxtRanges.push_back({X2 + (cur - X1), X2 + (R - X1)});
          cur = R + 1;
        }
        else if (cur < X1) {
          nxtRanges.push_back({cur, X1 - 1});
          cur = X1;
        }
        else assert(false);
      }
    }
    curRanges = nxtRanges;
  }
  cout << std::min_element(all(curRanges))->first << '\n';
}
