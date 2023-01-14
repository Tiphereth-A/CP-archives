#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const i64 MOD = 2004;
const i64 FACT[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
i64 m_choose_n(i64 m, i64 n) {
  if (n > m) return 0;
  i64 ans = 1;
  _rfor(i, m, m - n + 1) (ans *= i) %= MOD * FACT[n];
  return ans / FACT[n] % MOD;
}
int m[15];
int n, a, b;
i64 dfs(int now, int expm) {
  if (expm > b) return 0;
  if (now > n)
    return (m_choose_n(n + b - expm, n) + MOD -
            m_choose_n(n + a - expm - 1, n)) %
           MOD;
  return (dfs(now + 1, expm) + MOD - dfs(now + 1, expm + m[now] + 1)) % MOD;
}
auto solve() -> void {
  cin >> n >> a >> b;
  _for(i, 1, n) cin >> m[i];
  cout << dfs(1, 0);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
