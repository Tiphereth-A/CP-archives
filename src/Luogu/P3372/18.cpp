#include <bits/stdc++.h>
using u64 = uint64_t;
#define MAXN 100005
#define _for(i, l, r) for (unsigned long long(i) = (l); (i) <= (r); (i)++)
#define _rfor(i, l, r) for (unsigned long long i = l; i >= r; --i)
u64 tree[MAXN << 2], add[MAXN << 2];
u64 n, N = 1, m;
void build() {
  scanf("%lld%lld", &n, &m);
  for (; N <= n + 1; N <<= 1);
  _for(i, N + 1, N + n) scanf("%lld", tree + i);
  _rfor(i, N - 1, 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
}
void update(u64 s, u64 t, u64 k) {
  u64 lNum = 0, rNum = 0, nNum = 1;
  for (s = N + s - 1, t = N + t + 1; s ^ t ^ 1; s >>= 1, t >>= 1, nNum <<= 1) {
    tree[s] += k * lNum;
    tree[t] += k * rNum;
    if (~s & 1) {
      add[s ^ 1] += k;
      tree[s ^ 1] += k * nNum;
      lNum += nNum;
    }
    if (t & 1) {
      add[t ^ 1] += k;
      tree[t ^ 1] += k * nNum;
      rNum += nNum;
    }
  }
  for (; s; s >>= 1, t >>= 1) {
    tree[s] += k * lNum;
    tree[t] += k * rNum;
  }
}
u64 query(u64 s, u64 t) {
  u64 lNum = 0, rNum = 0, nNum = 1;
  u64 ans = 0;
  for (s = N + s - 1, t = N + t + 1; s ^ t ^ 1; s >>= 1, t >>= 1, nNum <<= 1) {
    if (add[s]) ans += add[s] * lNum;
    if (add[t]) ans += add[t] * rNum;
    if (~s & 1) {
      ans += tree[s ^ 1];
      lNum += nNum;
    }
    if (t & 1) {
      ans += tree[t ^ 1];
      rNum += nNum;
    }
  }
  for (; s; s >>= 1, t >>= 1) {
    ans += add[s] * lNum;
    ans += add[t] * rNum;
  }
  return ans;
}
int main() {
  build();
  char c = 0;
  u64 x = 0, y = 0, k = 0;
  while (m--) {
    scanf("%lld%lld%lld", &c, &x, &y);
    if (c & 2) printf("%lld\n", query(x, y));
    else {
      u64 k;
      scanf("%lld", &k);
      update(x, y, k);
    }
  }
  return 0;
}
