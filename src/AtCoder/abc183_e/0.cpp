#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 2e3 + OFFSET;
const int MOD = 1e9 + 7;
char maps[N][N];
i64 f[N][N][3];
int main() {
  int h, w;
  scanf("%d %d\n", &h, &w);
  for (int i = 1; i <= h; ++i) scanf("%s", maps[i] + 1);
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j)
      if (maps[i][j] == '.') {
        i64 now = ((i == 1 && j == 1) + f[i][j - 1][0] + f[i - 1][j][1] +
                   f[i - 1][j - 1][2]) %
                  MOD;
        f[i][j][0] = (f[i][j - 1][0] + now) % MOD;
        f[i][j][1] = (f[i - 1][j][1] + now) % MOD;
        f[i][j][2] = (f[i - 1][j - 1][2] + now) % MOD;
      }
  printf("%lld", (f[h][w - 1][0] + f[h - 1][w][1] + f[h - 1][w - 1][2]) % MOD);
  return 0;
}
