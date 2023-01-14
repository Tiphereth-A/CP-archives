#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define rfor_(i, r, l, v...) for (ll i = (r), i##e = (l), ##v; i >= i##e; --i)
#define Rep for_
#define rep rfor_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
const int MOD = 998244353;
void solve(int t_ = 0) {
  map<int, int> Map;
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1), tong(n + 1), b(n + 1);
  int cnt = 0;
  vector<int> fac(n + 1), inv(n + 1);
  auto KSM = [&](int x, int p) -> int {
    int ret = 1;
    while (p) {
      if (p & 1) ret = 1ll * ret * x % MOD;
      x = 1ll * x * x % MOD, p >>= 1;
    }
    return ret;
  };
  fac[0] = 1;
  Rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % MOD;
  inv[n] = KSM(fac[n], MOD - 2);
  rep(i, n - 1, 0) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
  auto C = [&](int n, int m) -> int {
    return 1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
  };
  Rep(i, 1, n) {
    cin >> a[i];
    if (!Map[a[i]]) Map[a[i]] = inc(cnt), b[cnt] = a[i];
    inc(tong[Map[a[i]]]);
  }
  int MAX = 0;
  Rep(i, 1, n) MAX = max(MAX, a[i]);
  int Ans = 0;
  Rep(k, 1, m) {
    if (k == MAX) {
      Ans = 1;
      Rep(i, 1, n) Ans = 1ll * Ans * C(k, a[i]) % MOD;
    }
    if (k > MAX) {
      int ret = KSM(k, n);
      Rep(i, 1, cnt) {
        ret = 1ll * ret *
              KSM(k - b[i], (1ll * (MOD - 2) * tong[i]) % (MOD - 1)) % MOD;
      }
      Ans = 1ll * Ans * ret % MOD;
    }
    cout << Ans << '\n';
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
