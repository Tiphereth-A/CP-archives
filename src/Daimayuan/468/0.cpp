#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t N = 101;
const uint32_t MOD = 998244353;
i64 a[N];
int a_cnt;
int main() {
  int n, k;
  cin >> n >> k;
  _for(i, 1ll, n) cin >> a[i];
  __int128_t ans = 0;
  i64 _1 = 0, _1pre = 0;
  _for(i, 1, n) {
    _1pre = _1;
    _1pre ^= _1 |= a[i];
    ans += (1ll << (k - __builtin_popcountll(_1))) *
           ((1ll << __builtin_popcountll(_1pre)) - 1) * i;
  }
  cout << (i64)(ans % MOD);
}
