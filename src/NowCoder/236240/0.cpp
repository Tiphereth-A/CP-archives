#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const i64 N = 1e6 + 5, MOD = 114514919810;
i64 f[N];
auto solve() -> void {
  int n;
  cin >> n;
  cout << f[n] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  f[1] = f[2] = 1;
  _for(i, 3, N - 1) f[i] = (f[i - 1] + f[i - 2] + 1) % MOD;
  _for(i, 2, N - 1) f[i] = (f[i] + f[i - 1]) % MOD;
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
