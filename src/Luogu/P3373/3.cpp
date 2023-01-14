#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define ls (p << 1)
#define rs (p << 1 | 1)
#define _mid int m = ((r - l) >> 1) + l
const int N = 1e6 + 5;
int n;
i64 a[N], mod;
struct node {
  i64 sum, add, mul;
} tr[N << 2];
void push_up(int p) { tr[p].sum = (tr[ls].sum + tr[rs].sum) % mod; }
void push_down(int p, int len_l, int len_r) {
  tr[ls].add = ((tr[ls].add * tr[p].mul) % mod + tr[p].add) % mod;
  tr[ls].mul = (tr[ls].mul * tr[p].mul) % mod;
  tr[ls].sum =
    ((tr[ls].sum * tr[p].mul) % mod + (tr[p].add * len_l) % mod) % mod;
  tr[rs].add = ((tr[rs].add * tr[p].mul) % mod + tr[p].add) % mod;
  tr[rs].mul = (tr[rs].mul * tr[p].mul) % mod;
  tr[rs].sum =
    ((tr[rs].sum * tr[p].mul) % mod + (tr[p].add * len_r) % mod) % mod;
  tr[p].add = 0;
  tr[p].mul = 1;
}
void build(int l = 1, int r = n, int p = 1) {
  tr[p].add = 0;
  tr[p].mul = 1;
  if (l == r) {
    tr[p].sum = a[l];
    return;
  }
  _mid;
  build(l, m, ls);
  build(m + 1, r, rs);
  push_up(p);
}
void update(int L, int R, i64 k, int flag, int l = 1, int r = n, int p = 1) {
  if (L <= l && r <= R) {
    if (flag) {
      tr[p].sum = (tr[p].sum + (k * (r - l + 1)) % mod) % mod;
      tr[p].add = (tr[p].add + k) % mod;
    } else {
      tr[p].sum = (tr[p].sum * k) % mod;
      tr[p].mul = (tr[p].mul * k) % mod;
      tr[p].add = (tr[p].add * k) % mod;
    }
    return;
  }
  _mid;
  push_down(p, m - l + 1, r - m);
  if (L <= m) update(L, R, k, flag, l, m, ls);
  if (R > m) update(L, R, k, flag, m + 1, r, rs);
  push_up(p);
}
i64 query(int L, int R, int l = 1, int r = n, int p = 1) {
  if (L <= l && r <= R) return tr[p].sum;
  _mid;
  push_down(p, m - l + 1, r - m);
  i64 ans = 0;
  if (L <= m) ans = (ans + query(L, R, l, m, ls)) % mod;
  if (R > m) ans = (ans + query(L, R, m + 1, r, rs)) % mod;
  return ans;
}
int main() {
  int m;
  scanf("%d%d%lld", &n, &m, &mod);
  _for(i, 1, n) scanf("%lld", a + i);
  build();
  while (m--) {
    int o, x, y;
    i64 k;
    scanf("%d%d%d", &o, &x, &y);
    switch (o) {
      case 1:
        scanf("%lld", &k);
        update(x, y, k, 0);
        break;
      case 2:
        scanf("%lld", &k);
        update(x, y, k, 1);
        break;
      case 3: printf("%lld\n", query(x, y)); break;
    }
  }
  return 0;
}
