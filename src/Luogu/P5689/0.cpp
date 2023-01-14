#include <bits/stdc++.h>
#define dbg(...) 42
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
template <class Tp>
using vec = vector<Tp>;
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define rfors_(i, r, l, s, ...) \
  for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)
#define rfor_(i, r, l, ...) rfors_(i, r, l, 1 __VA_OPT__(, ) __VA_ARGS__)
const u32 MOD = 1e9 + 7;
constexpr u64 qpow(u64 a, u64 b) {
  u64 ans = 1;
  for (; b; b /= 2, a = a * a % MOD)
    if (b & 1) ans = ans * a % MOD;
  return ans;
}
void solve([[maybe_unused]] int t_ = 0) {
  u32 n, q;
  cin >> n >> q;
  vec<u32> fa(n + 1);
  iota(fa.begin(), fa.end(), 0);
  auto find = [&](auto &&f, u32 x) -> u32 {
    return x == fa[x] ? x : fa[x] = f(f, fa[x]);
  };
  u32 ans = 0;
  auto get = [&]() {
    u32 x;
    cin >> x;
    return find(find, (x + ans) % n);
  };
  vec<u64> fact(n + 1), ifact(n + 1);
  fact[0] = ifact[0] = 1;
  for_(i, 1, n) fact[i] = fact[i - 1] * i % MOD;
  ifact[n] = qpow(fact[n], MOD - 2);
  rfor_(i, n - 1, 1) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
  auto mCn = [&](u32 m, u32 n) {
    return m < n ? 0 : fact[m] * ifact[n] % MOD * ifact[m - n] % MOD;
  };
  vec<u32> w(n + 1, 1);
  vec<u64> a(n + 1, 1);
  while (q--) {
    u32 op;
    cin >> op;
    if (op == 1) {
      u32 x = get(), y = get();
      w[y] += w[x];
      a[y] = a[y] * a[x] % MOD * mCn(w[y] - 1, w[x]) % MOD;
      fa[x] = y;
    } else {
      u32 x = get();
      cout << (ans = a[x]) << '\n';
    }
  }
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cerr << fixed << setprecision(6);
  int i_ = 0;
  dbg(i_), solve(i_);
  return 0;
}
