#include <bits/stdc++.h>
#define int long long
#define Rep(i, a, b) for (int i = (a), i##Limit = (b); i <= i##Limit; ++i)
#define rep(i, a, b) for (int i = (a), i##Limit = (b); i >= i##Limit; --i)
using namespace std;
const int Mod = 1000000007, INV2 = (1000000007 + 1) / 2,
          INV3 = (1000000007 + 1) / 3;
int KSM(int x, int p) {
  int ret = 1;
  while (p) {
    if (p & 1) (ret *= x) %= Mod;
    (x *= x) %= Mod, p >>= 1;
  }
  return ret;
}
signed main() {
  int n, m, S = 0;
  cin >> n >> m;
  vector<int> A(n), pre(n), suf(n);
  Rep(i, 0, n - 1) cin >> A[i], (S += A[i]) %= Mod;
  Rep(i, 0, n - 1) pre[i] = (i == 0 ? A[i] : (A[i] + pre[i - 1]) % Mod);
  rep(i, n - 1, 0) suf[i] = (i == n - 1 ? A[i] : (A[i] + suf[i + 1]) % Mod);
  Rep(i, 0, n - 1) pre[i] = (i == 0 ? pre[i] : (pre[i] + pre[i - 1]) % Mod);
  rep(i, n - 1, 0) suf[i] = (i == n - 1 ? suf[i] : (suf[i] + suf[i + 1]) % Mod);
  auto sum1 = [](int n) -> int { return n * (n + 1) % Mod * INV2 % Mod; };
  auto sum2 = [](int n) -> int {
    return n * (n + 1) % Mod * (2 * n + 1) % Mod * INV2 % Mod * INV3 % Mod;
  };
  int Sum1, Sum2, x = KSM(2, m);
  Sum1 = Sum2 = (((n * (sum1(x - 1)) % Mod) + Mod) % Mod) * S % Mod;
  (Sum1 += x * pre[n - 1] % Mod) %= Mod;
  (Sum2 += (x * INV2 % Mod) * (pre[n - 1] + suf[0]) % Mod) %= Mod;
  cout << max(Sum1, Sum2);
  return 0;
}
