#include <bits/stdc++.h>
using namespace std;
char mat[25][25];
int main() {
#define _(x, y)              \
  {                          \
    consec_##y = 0;          \
    ++cnt_##x;               \
    if (++consec_##x >= 3) { \
      cout << 0;             \
      return 0;              \
    }                        \
  }
#define __(r, c)                                                        \
  for (int row = 0, cnt_w, cnt_b, consec_w, consec_b; row < n; ++row) { \
    cnt_w = cnt_b = consec_w = consec_b = 0;                            \
    for (int col = 0; col < n; ++col)                                   \
      if (mat[r][c] == 'B') _(b, w)                                     \
      else if (mat[r][c] == 'W') _(w, b)                                \
    if (cnt_w != cnt_b) {                                               \
      cout << 0;                                                        \
      return 0;                                                         \
    }                                                                   \
  }
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> mat[i];
  __(row, col);
  __(col, row);
  cout << 1;
  return 0;
}
