#include <bits/stdc++.h>
using namespace std;
const int N = 35;
i64 a[N], dp[N][N][N];
i64 f(int l, int r, int root) {
  if (l > r) return 1;
  if (l == r) return dp[l][r][root] = a[root];
  if (dp[l][r][root]) return dp[l][r][root];
  i64 max_l = 1, max_r = 1;
  for (int root_l = l; root_l < root; ++root_l)
    max_l = max(max_l, f(l, root - 1, root_l));
  for (int root_r = root + 1; root_r <= r; ++root_r)
    max_r = max(max_r, f(root + 1, r, root_r));
  return dp[l][r][root] = max_l * max_r + a[root];
}
void print(int l, int r, int root) {
  if (l > r) return;
  cout << root << " ";
  int _r = l;
  i64 ans = 0;
  for (int i = l; i < root; ++i)
    if (ans < f(l, root - 1, i)) ans = dp[l][root - 1][_r = i];
  print(l, root - 1, _r);
  _r = root + 1;
  ans = 0;
  for (int i = root + 1; i <= r; ++i)
    if (ans < f(root + 1, r, i)) ans = dp[root + 1][r][_r = i];
  print(root + 1, r, _r);
}
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  i64 ans = 0;
  int root = 1;
  for (int r = 1; r <= n; ++r)
    if (ans < f(1, n, r)) ans = dp[1][n][root = r];
  cout << ans << endl;
  print(1, n, root);
  return 0;
}
