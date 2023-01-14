#include <bits/stdc++.h>
std::map<int, int> list;
int mod;
void err() { puts("Orz, I cannot find x!"); }
int qpow(i64 a, i64 b) {
  int ans = 1;
  for (; b; a = a * a % mod, b >>= 1)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
void bsgs(int x, int y) {
  list.clear();
  if (y == 1) {
    puts("0");
    return;
  }
  int m = sqrt(mod) + 1, s = y, tmp, ans = -1;
  for (int b = 0; b < m; ++b) {
    list[s] = b;
    s = 1ll * s * x % mod;
  }
  tmp = qpow(x, m);
  s = 1;
  for (int a = 1; a <= m + 1; ++a) {
    s = 1ll * s * tmp % mod;
    if (list.count(s)) {
      ans = a * m - list[s];
      break;
    }
  }
  if (~ans) printf("%d\n", ans);
  else err();
}
int main() {
  int t, k, y, z;
  scanf("%d%d", &t, &k);
  switch (k) {
    case 1:
      while (t--) {
        scanf("%d%d%d", &y, &z, &mod);
        printf("%d\n", qpow(y, z));
      }
      break;
    case 2:
      while (t--) {
        scanf("%d%d%d", &y, &z, &mod);
        int tmp = (y % mod) ? 1 : mod;
        if (z % tmp) err();
        else printf("%lld\n", 1ll * qpow(y, mod - 2) * z % mod);
      }
      break;
    case 3:
      while (t--) {
        scanf("%d%d%d", &y, &z, &mod);
        if (y % mod) bsgs(y % mod, z % mod);
        else err();
      }
  }
  return 0;
}
