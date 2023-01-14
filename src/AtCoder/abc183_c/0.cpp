#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int g[N][N];
int p[N];
int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) cin >> g[i][j];
  for (int i = 1; i <= n; ++i) p[i] = i;
  int ans = 0;
  do {
    int len = g[p[n]][1];
    for (int now_idx = 2, pre, now; now_idx <= n; ++now_idx) {
      pre = p[now_idx - 1];
      now = p[now_idx];
      len += g[pre][now];
    }
    ans += len == k;
  } while (next_permutation(p + 2, p + n + 1));
  cout << ans;
  return 0;
}
