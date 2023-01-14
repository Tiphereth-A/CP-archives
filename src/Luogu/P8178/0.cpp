#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e3 + OFFSET;
template <typename T = i64>
T exgcd(T a, T b, T &x, T &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T res = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return res;
}
template <typename Tp = i64>
constexpr Tp inv(Tp a, const Tp &mod) {
  Tp res(1), b = mod - 2;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i64 a[N], b[N], p[N];
struct Equs {
  i64 b, p;
  bool operator<(const Equs &rhs) const {
    return p == rhs.p ? b < rhs.b : p < rhs.p;
  }
  bool operator==(const Equs &rhs) const { return b == rhs.b && p == rhs.p; }
} q[N];
void solve() {
  int k;
  cin >> k;
  _for(i, 1, k) cin >> a[i];
  _for(i, 1, k) cin >> b[i];
  _for(i, 1, k) cin >> p[i];
  int cnt = 0;
  _for(i, 1, k) {
    q[cnt] = {0, p[i]};
    i64 _a = 1;
    _rfor(j, i, 1) {
      (q[cnt].b += _a * b[j] % p[i]) %= p[i];
      (_a *= a[j]) %= p[i];
    }
    if (_a == 0) {
      if (q[cnt].b) {
        cout << "No\n";
        return;
      }
      continue;
    }
    q[cnt++].b = (p[i] - q[cnt].b) * inv(_a, p[i]) % p[i];
  }
  if (!cnt) {
    cout << "Yes\n";
    return;
  }
  sort(q, q + cnt);
  _for(i, 1, cnt - 1)
    if (q[i].p == q[i - 1].p && q[i].b != q[i - 1].b) {
      cout << "No\n";
      return;
    }
  cout << "Yes\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
