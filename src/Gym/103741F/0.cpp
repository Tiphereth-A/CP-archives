#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int N = 1e7 + 5, P = 6e6 + 5;
bool vis[N];
int prime[P], cnt_prime;
int mu[N];
void init_prime(const int &n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      mu[i] = -1;
      prime[++cnt_prime] = i;
    }
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
}
constexpr i128 qpow(i128 a, i128 b) {
  i128 res(1);
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
};
auto solve() -> void {
  i64 l, r, k;
  cin >> l >> r >> k;
  i64 ans = r - l + 1;
  if (k > 50) _run_return_void(cout << ans);
  for (i64 i = 2, __; (__ = qpow(i, k)) <= r; ++i) {
    if (!mu[i]) continue;
    ans += mu[i] * (r / __ - (l - 1) / __);
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  init_prime();
  solve();
  return 0;
}
