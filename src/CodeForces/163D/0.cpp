#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
using u32 = uint32_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) \
  for (make_signed_t<decltype(r - l)> i = (r), ##vals; i >= (l); --i)
const int N = 64;
u64 n, v;
u64 p[N][N];
u32 k[N];
u64 a, b, c, ans;
void dfs_b(const u64 &&now_n, const u64 &&_b, const u64 &&_a) {
  if (_b * _b * _a > v) return;
  if (now_n > n) {
    const u64 &&_c = v / _a / _b;
    if (_a * _b + _b * _c + _c * _a < ans) {
      ans = _a * _b + _b * _c + _c * _a;
      a = _a;
      b = _b;
      c = _c;
    }
    return;
  }
  const u64 * const _p = p[now_n];
  _rfor(i, k[now_n], 0) {
    k[now_n] -= i;
    dfs_b(now_n + 1, _b * _p[i], move(_a));
    k[now_n] += i;
  }
}
void dfs_a(const u64 &&now_n, const u64 &&_a) {
  if (_a * _a * _a > v) return;
  if (now_n > n) {
    const u64 &&_va = v / _a;
    if (ans <= 2 * _a * sqrt(_va) + _va) return;
    dfs_b(1, 1, move(_a));
    return;
  }
  const u64 * const _p = p[now_n];
  _rfor(i, k[now_n], 0) {
    k[now_n] -= i;
    dfs_a(now_n + 1, _a * _p[i]);
    k[now_n] += i;
  }
}
auto __STATIC__ = []() {
  _for(i, 0, N - 1) p[i][0] = 1;
  return 0;
}();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    cin >> n;
    v = 1;
    _for(i, 1, n) cin >> p[i][1] >> k[i];
    _for(i, 1, n)
      _for(j, 1, k[i]) p[i][j] = p[i][j - 1] * p[i][1];
    _for(i, 1, n) v *= p[i][k[i]];
    a = 1;
    b = 1;
    c = v;
    ans = a * b + b * c + c * a;
    dfs_a(1, 1);
    cout << ans * 2 << ' ' << a << ' ' << b << ' ' << c << '\n';
  }
  return 0;
}
