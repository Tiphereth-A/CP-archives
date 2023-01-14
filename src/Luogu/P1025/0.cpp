#include <bits/stdc++.h>
using namespace std;
int n, k, ans;
void dfs(int rn, int rk, int sum) {
  if (rk == k) {
    if (sum == n) ans++;
    return;
  }
  int m = (n - sum) / (k - rk) + 1;
  for (int i = rn; i <= m; i++) dfs(i, rk + 1, sum + i);
  return;
}
int main() {
  cin >> n >> k;
  dfs(1, 0, 0);
  cout << ans;
  return 0;
}
