#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 16 + 1;
int a[N][N], f[N][N][(1 << (N - 1)) + 1];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, r, c;
  cin >> n >> m >> r >> c;
  _for(i, 1, n)
    _for(j, 1, m) cin >> a[i][j];
  _for(i, 1, m)
    _for(j, 1, n) memset(f[i][j], 0x3f, sizeof(f[i][j][0]) * (1 << n));
  int ans = INT32_MAX;
  _for(i, 1, m)
    _for(state_row, (1 << r) - 1, (1 << n) - 1) {
      vector<int *> vec;
      for (int _ = 0; (1 << _) <= state_row; ++_)
        if ((1 << _) & state_row) vec.push_back(a[_ + 1]);
      if (vec.size() != r) continue;
      int score_i = 0;
      for (auto it = vec.begin() + 1; it != vec.end(); ++it)
        score_i += abs((*it)[i] - (*(it - 1))[i]);
      _for(j, 1, min(i, c))
        _for(k, j - 1, i - 1, score) {
          score = 0;
          if (k)
            for (const auto &p : vec) score += abs(p[k] - p[i]);
          f[i][j][state_row] =
            min(f[i][j][state_row], f[k][j - 1][state_row] + score + score_i);
        }
      ans = min(ans, f[i][c][state_row]);
    }
  cout << ans;
  return 0;
}
