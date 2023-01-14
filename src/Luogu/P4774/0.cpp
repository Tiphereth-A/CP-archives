#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class _T>
bool chkmin(_T &a, _T b) {
  return b < a ? a = b, true : false;
}
template <class _T>
bool chkmax(_T &a, _T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  i128 res = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return res;
}
i64 a[N], p[N], _b[N], b[N];
i64 mindmg = 0;
bool excrt(i64 n, i64 &res) {
  i128 A, B, M = 1, pre_M;
  i128 x = 0, R;
  i128 g, lambda, mu;
  for (i64 i = 1; i <= n; ++i) {
    A = b[i] * (pre_M = M) % (B = p[i]);
    R = (a[i] - b[i] * x % B + B) % B;
    g = exgcd(A, B, lambda, mu);
    ((lambda %= B) += B) %= B;
    if (R % g) return false;
    M *= B / g;
    (x += lambda * (R / g) % (B / g) * pre_M % M) %= M;
  }
  res = x + (x < mindmg ? ((mindmg - x - 1) / M + 1) * M : 0);
  return true;
}
multiset<i64> all_b;
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    _for(i, 1, n) scanf("%lld", a + i);
    _for(i, 1, n) scanf("%lld", p + i);
    _for(i, 1, n) scanf("%lld", _b + i);
    i64 _;
    _for(i, 1, m) {
      scanf("%lld", &_);
      all_b.insert(_);
    }
    _for(i, 1, n) {
      auto now = all_b.upper_bound(a[i]);
      if (now != all_b.begin()) --now;
      b[i] = *now;
      all_b.erase(now);
      all_b.insert(_b[i]);
      chkmax(mindmg, (a[i] - 1) / b[i] + 1);
    }
    i64 res = 0;
    if (excrt(n, res)) printf("%lld\n", res);
    else puts("-1");
  __end_kase:;
    all_b.clear();
    mindmg = 0;
  }
FINISHED:
  return 0;
}
