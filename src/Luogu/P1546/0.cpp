#include <bits/stdc++.h>
using namespace std;
struct Node {
  int x, y, w;
} a[200005];
int f[200005];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = i;
    for (int j = 1, k; j <= n; j++) {
      cin >> k;
      if (j > i) a[++cnt] = {i, j, k};
    }
  }
  sort(
    a + 1, a + cnt + 1, [](auto &&lhs, auto &&rhs) { return lhs.w < rhs.w; });
  int ans = 0, p = 1;
  for (int i = 1; i <= cnt; i++) {
    if (find(a[i].x) != find(a[i].y)) {
      ans += a[i].w;
      f[find(a[i].x)] = a[i].y;
      if (++p == n) break;
    }
  }
  cout << ans;
  return 0;
}
