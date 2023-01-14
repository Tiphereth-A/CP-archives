#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define ls rt << 1
#define rs rt << 1 | 1
#define Mid int m = ((r - l) >> 1) + l
typedef long long ll;
#define MAXN 1000005
ll sum[MAXN << 2], add[MAXN << 2], a[MAXN];
void PushUp(ll rt) { sum[rt] = sum[ls] + sum[rs]; }
void PushDown(ll rt, ll ln, ll rn) {
  add[ls] += add[rt];
  sum[ls] += add[rt] * ln;
  add[rs] += add[rt];
  sum[rs] += add[rt] * rn;
  add[rt] = 0;
}
void Build(ll l, ll r, ll rt) {
  if (l == r) {
    sum[rt] = a[l];
    return;
  }
  Mid;
  Build(l, m, ls);
  Build(m + 1, r, rs);
  PushUp(rt);
}
void Update(ll L, ll R, ll c, ll l, ll r, ll rt) {
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
ll Query(ll L, ll R, ll l, ll r, ll rt) {
  ll ans = 0;
  if (L <= l && r <= R) return sum[rt];
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) ans += Query(L, R, l, m, ls);
  if (R > m) ans += Query(L, R, m + 1, r, rs);
  return ans;
}
int main() {
  ll n, m;
  scanf("%lld%lld", &n, &m);
  _for(i, 1, n) scanf("%lld", &a[i]);
  Build(1, n, 1);
  while (m--) {
    ll o, x, y;
    scanf("%lld", &o);
    if (o == 1) {
      ll k;
      scanf("%lld%lld%lld", &x, &y, &k);
      Update(x, y, k, 1, n, 1);
    } else if (o == 2) {
      scanf("%lld%lld", &x, &y);
      printf("%lld\n", Query(x, y, 1, n, 1));
    }
  }
  return 0;
}
