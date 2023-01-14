#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
int n, m, tree[4000005];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &tree[n + i]);
  tree[2 * n + 1] = INF;
  for (int i = n; i; --i) tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
  puts("0");
  for (int i = 2; i <= n; ++i) {
    int l = std::max(n, i - m - 1 + n), r = i + n, ans = INF;
    while (l ^ r ^ 1) {
      if (~l & 1) ans = std::min(tree[l ^ 1], ans);
      if (r & 1) ans = std::min(tree[r ^ 1], ans);
      l >>= 1, r >>= 1;
    }
    printf("%d\n", ans);
  }
  return 0;
}
