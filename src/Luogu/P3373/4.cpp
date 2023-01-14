#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define ls p << 1
#define rs p << 1 | 1
#define Mid int m = ((r - l) >> 1) + l
typedef long long ll;
#define MAXN 1000005
ll sum[MAXN << 2], add[MAXN << 2], mul[MAXN << 2], a[MAXN], mod;
void PushUp(int p) { sum[p] = (sum[ls] + sum[rs]) % mod; }
void PushDown(int p, int ln, int rn) {
  add[ls] = ((add[ls] * mul[p]) % mod + add[p]) % mod;
  mul[ls] = (mul[ls] * mul[p]) % mod;
  sum[ls] = ((sum[ls] * mul[p]) % mod + (add[p] * ln) % mod) % mod;
  add[rs] = ((add[rs] * mul[p]) % mod + add[p]) % mod;
  mul[rs] = (mul[rs] * mul[p]) % mod;
  sum[rs] = ((sum[rs] * mul[p]) % mod + (add[p] * rn) % mod) % mod;
  add[p] = 0;
  mul[p] = 1;
}
void Build(int l, int r, int p) {
  add[p] = 0;
  mul[p] = 1;
  if (l == r) {
    sum[p] = a[l];
    return;
  }
  Mid;
  Build(l, m, ls);
  Build(m + 1, r, rs);
  PushUp(p);
}
void Update(int L, int R, ll k, int l, int r, int p, int f) {
  if (L <= l && r <= R) {
    if (f) {
      sum[p] = (sum[p] + (k * (r - l + 1)) % mod) % mod;
      add[p] = (add[p] + k) % mod;
    } else {
      sum[p] = (sum[p] * k) % mod;
      mul[p] = (mul[p] * k) % mod;
      add[p] = (add[p] * k) % mod;
    }
    return;
  }
  Mid;
  PushDown(p, m - l + 1, r - m);
  if (L <= m) Update(L, R, k, l, m, ls, f);
  if (R > m) Update(L, R, k, m + 1, r, rs, f);
  PushUp(p);
}
ll Query(int L, int R, int l, int r, int p) {
  if (L <= l && r <= R) return sum[p];
  Mid;
  PushDown(p, m - l + 1, r - m);
  ll ans = 0;
  if (L <= m) ans = (ans + Query(L, R, l, m, ls)) % mod;
  if (R > m) ans = (ans + Query(L, R, m + 1, r, rs)) % mod;
  return ans;
}
int main() {
  int n, m;
  scanf("%d%d%lld", &n, &m, &mod);
  _for(i, 1, n) scanf("%lld", &a[i]);
  Build(1, n, 1);
  while (m--) {
    int o, x, y;
    ll k;
    scanf("%d", &o);
    switch (o) {
      case 1:
        scanf("%d%d%lld", &x, &y, &k);
        Update(x, y, k, 1, n, 1, 0);
        break;
      case 2:
        scanf("%d%d%lld", &x, &y, &k);
        Update(x, y, k, 1, n, 1, 1);
        break;
      case 3:
        scanf("%d%d", &x, &y);
        printf("%lld\n", Query(x, y, 1, n, 1));
        break;
    }
  }
  return 0;
}
