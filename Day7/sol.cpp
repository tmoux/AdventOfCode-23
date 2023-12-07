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

map<char, int> MP = {
{'A', 0},
{'K', 1},
{'Q', 2},
{'T', 3},
{'9', 4},
{'8', 5},
{'7', 6},
{'6', 7},
{'5', 8},
{'4', 9},
{'3', 10},
{'2', 11},
{'J', 12},
};

bool compString(string a, string b) {
  F0R(i, 5) {
    if (MP[a[i]] != MP[b[i]]) {
      return MP[a[i]] < MP[b[i]];
    }
  }
  return false;
}

struct Card {
  static int getConst(const string& s) {
    map<char, int> mp;
    for (char c: s) mp[c]++;
    map<int, int> freq;
    for (auto [_, c]: mp) freq[c]++;
    if (freq.count(5)) return 0;
    else if (freq.count(4)) return 1;
    else if (freq.count(3) && freq.count(2)) return 3;
    else if (freq.count(3)) return 4;
    else if (freq.count(2) && freq[2] >= 2) return 5;
    else if (freq.count(2)) return 6;
    else return 7;
  }

  string hand;
  int bid;
  int type;

  void rec(string cur, vector<string>& v, const map<char, int>& mp) const {
    if (sz(cur) == 5) v.push_back(cur);
    else {
      int i = sz(cur);
      if (hand[i] == 'J') {
        for (auto [c, _]: mp) {
          cur += c;
          rec(cur, v, mp);
          cur.pop_back();
        }
      }
      else {
        cur += hand[i];
        rec(cur, v, mp);
        cur.pop_back();
      }
    }
  }

  int computeType() {
    map<char, int> mp;
    for (char c: hand) {
      if (c != 'J') mp[c]++;
    }
    // All J's
    if (mp.empty()) return 0;
    vector<string> v;
    rec("", v, mp);
    int ret = 7;
    for (auto s: v) {
      ckmin(ret, getConst(s));
    }
    return ret;
  }

  Card(string _hand, int _bid) : hand(_hand), bid(_bid), type(computeType()) {}

  bool operator<(const Card& rhs) const {
    return rhs > *this;
  }
  bool operator>(const Card& rhs) const {
    if (type != rhs.type) return type < rhs.type;
    else return compString(hand, rhs.hand);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string hand;
  int bid;

  vector<Card> cards;
  while (cin >> hand >> bid) {
    cards.push_back({hand, bid});
  }
  sort(all(cards));

  ll ans = 0;
  F0R(i, sz(cards)) {
    ans += (i + 1) * cards[i].bid;
  }
  cout << ans << endl;
}
