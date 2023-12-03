#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define sz(x) (int)(x).size()

int main() {
  vector<string> grid;
  string line;
  while (cin >> line) grid.push_back(line);
  int N = grid.size();
  int M = grid[0].size();
  auto isSymbol = [&](char c) { return !(isdigit(c) || c == '.'); };
  auto valid = [&](int i, int j) -> bool { return 0 <= i && i < N && 0 <= j && j < M; };
  vector<vector<vector<int>>> V(N, vector<vector<int>>(M));

  int part1 = 0;
  F0R(i, N) {
    F0R(j, M) {
      if (j < M && isdigit(grid[i][j])) {
        int n = 0;
        int l = j;
        while (isdigit(grid[i][j])) {
          n = n * 10 + (grid[i][j++] - '0');
        }
        int r = j-1;

        bool p = false;
        FOR(k, l-1, r+2) {
          FOR(ii, i-1, i+2) {
            bool b = valid(ii, k) && isSymbol(grid[ii][k]);
            p |= b;
            if (b) V[ii][k].push_back(n);
          }
        }
        if (p) part1 += n;
      }
    }
  }

  int part2 = 0;
  F0R(i, N) {
    F0R(j, M) {
      if (grid[i][j] == '*' && sz(V[i][j]) == 2) {
        part2 += V[i][j][0] * V[i][j][1];
      }
    }
  }

  cout << "Part 1: " << part1 << '\n';
  cout << "Part 2: " << part2 << '\n';
}
