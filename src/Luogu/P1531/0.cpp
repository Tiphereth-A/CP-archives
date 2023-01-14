#include <bits/stdc++.h>
const int MAXN = 2e5 + 5;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (auto i = (l); i >= (r); --i)
int a[MAXN << 2], t[MAXN << 2];
int n, N = 1, m;
int Max(int a, int b) { return a > b ? a : b; }
void build() {
  _for(i, 1, n) t[N + i] = a[i];
  _rep(i, N - 1, 1) t[i] = Max(t[i << 1], t[i << 1 | 1]);
}
void modify(int x, int k) {
  for (int i = N + x; i; i >>= 1) t[i] = Max(t[i], k);
}
int query(int x, int y) {
  int ans = 0;
  for (int s = N + x - 1, r = N + y + 1; s ^ r ^ 1; s >>= 1, r >>= 1) {
    if (~s & 1) ans = Max(ans, t[s ^ 1]);
    if (r & 1) ans = Max(ans, t[r ^ 1]);
  }
  return ans;
}
int main() {
  std::cin >> n >> m;
  while (N < n + 2) N <<= 1;
  _for(i, 1, n) std::cin >> a[i];
  build();
  while (m--) {
    char c;
    int x, y;
    std::cin >> c >> x >> y;
    if (c == 'Q') std::cout << query(x, y) << std::endl;
    else modify(x, y);
  }
  return 0;
}
