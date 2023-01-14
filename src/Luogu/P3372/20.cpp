#include <bits/stdc++.h>
using u64 = uint64_t;
#define _for(i, l, r) for (unsigned long long i = (l); i <= (r); ++i)
#define ls rt << 1
#define rs rt << 1 | 1
#define Mid unsigned long long m = ((r - l) >> 1) + l
#define MAXN 100005
u64 sum[MAXN << 2], add[MAXN << 2], a[MAXN];
void PushUp(const u64 &rt) { sum[rt] = sum[ls] + sum[rs]; }
void PushDown(const u64 &rt, const u64 &ln, const u64 &rn) {
  add[ls] += add[rt];
  sum[ls] += add[rt] * ln;
  add[rs] += add[rt];
  sum[rs] += add[rt] * rn;
  add[rt] = 0;
}
void Build(const u64 &l, const u64 &r, const u64 &rt) {
  if (l == r) {
    sum[rt] = a[l];
    return;
  }
  Mid;
  Build(l, m, ls);
  Build(m + 1, r, rs);
  PushUp(rt);
}
void Update(const u64 &L,
            const u64 &R,
            const u64 &c,
            const u64 &l,
            const u64 &r,
            const u64 &rt) {
  if (L <= l && r <= R) {
    sum[rt] += c * (r - l + 1);
    add[rt] += c;
    return;
  }
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) Update(L, R, c, l, m, ls);
  if (R > m) Update(L, R, c, m + 1, r, rs);
  PushUp(rt);
}
u64 Query(
  const u64 &L, const u64 &R, const u64 &l, const u64 &r, const u64 &rt) {
  u64 ans = 0;
  if (L <= l && r <= R) return sum[rt];
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) ans += Query(L, R, l, m, ls);
  if (R > m) ans += Query(L, R, m + 1, r, rs);
  return ans;
}
int main() {
  u64 n = 0, m = 0;
  scanf("%lld%lld", &n, &m);
  _for(i, 1, n) scanf("%lld", &a[i]);
  Build(1, n, 1);
  u64 o = 0, x = 0, y = 0, k = 0;
  while (m--) {
    scanf("%lld", &o);
    if (o & 1) {
      scanf("%lld%lld%lld", &x, &y, &k);
      Update(x, y, k, 1, n, 1);
    } else {
      scanf("%lld%lld", &x, &y);
      printf("%lld\n", Query(x, y, 1, n, 1));
    }
  }
  return 0;
}
