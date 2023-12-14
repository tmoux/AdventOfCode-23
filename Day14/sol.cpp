#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

int main() {
  string line;
  vector<string> grid;
  while (cin >> line) {
    grid.push_back(line);
  }
  int N = grid.size(), M = grid[0].size();

  auto up = [&](vector<string>& g) -> void {
    F0R(i, N) {
      F0R(j, M) {
        if (g[i][j] == 'O') {
          int k = i;
          while (k-1 >= 0 && g[k-1][j] == '.') k--;
          g[i][j] = '.';
          g[k][j] = 'O';
        }
      }
    }
  };

  auto down = [&](vector<string>& g) -> void {
    F0Rd(i, N) {
      F0R(j, M) {
        if (g[i][j] == 'O') {
          int k = i;
          while (k+1 < N && g[k+1][j] == '.') k++;
          g[i][j] = '.';
          g[k][j] = 'O';
        }
      }
    }
  };

  auto left = [&](vector<string>& g) -> void {
    F0R(i, N) {
      F0R(j, M) {
        if (g[i][j] == 'O') {
          int k = j;
          while (k-1 >= 0 && g[i][k-1] == '.') k--;
          g[i][j] = '.';
          g[i][k] = 'O';
        }
      }
    }
  };

  auto right = [&](vector<string>& g) -> void {
    F0R(i, N) {
      F0Rd(j, M) {
        if (g[i][j] == 'O') {
          int k = j;
          while (k+1 < N && g[i][k+1] == '.') k++;
          g[i][j] = '.';
          g[i][k] = 'O';
        }
      }
    }
  };

  auto calcTotalLoad = [&](const vector<string>& g) -> int {
    int ans = 0;
    F0R(i, N) {
      F0R(j, M) {
        if (g[i][j] == 'O') ans += N - i;
      }
    }
    return ans;
  };

  // Part 1
  auto part1Grid = grid;
  up(part1Grid);
  cout << "Part 1: " << calcTotalLoad(part1Grid) << '\n';

  // Part 2
  map<vector<string>, int> MP;
  vector<vector<string>> grids;

  int K = 1000000000;
  F0R(i, K+1) {
    if (MP.count(grid)) {
      int d = i - MP[grid];
      grid = grids[MP[grid] + (K - MP[grid]) % d];
      break;
    }
    else {
      MP[grid] = i;
      grids.push_back(grid);
      up(grid);
      left(grid);
      down(grid);
      right(grid);
    }
  }

  cout << "Part 2: " << calcTotalLoad(grid) << endl;
}
