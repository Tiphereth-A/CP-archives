#include <bits/stdc++.h>
const int N = 1e4 + 5;
#define max(a, b) (((a) > (b)) ? (a) : (b))
using std::cin;
using std::cout;
i64 f[N][N];
int main() {
  int r, ans = 0;
  cin >> r;
  for (int i = 1; i <= r; i++)
    for (int j = 1; j <= i; j++) cin >> f[i][j];
  for (int i = 2; i <= r; i++)
    for (int j = 1; j <= i; j++) f[i][j] += max(f[i - 1][j], f[i - 1][j - 1]);
  for (int i = 1; i <= r; i++) ans = max(ans, f[r][i]);
  cout << ans;
  return 0;
}
