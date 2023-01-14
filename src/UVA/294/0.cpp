#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 1e5 + 5, P = 1e4 + 5;
bool vis[N];
int prime[P], cnt_prime;
void init_prime(const int &n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt_prime] = i;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
init_prime();
return 0;
}
();
i64 tau(i64 x) {
  i64 ret = 1;
  _for(i, 1ll, cnt_prime, cnt) {
    if (x < prime[i]) break;
    if (x % prime[i] == 0) {
      cnt = 0;
      while (x % prime[i] == 0) {
        ++cnt;
        x /= prime[i];
      }
      ret *= cnt + 1;
    }
  }
  if (x > 1) ret *= 2;
  return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  while (kase--) {
    i64 l, r;
    cin >> l >> r;
    i64 ans = 0, cnt = 0;
    _for(i, l, r, _cnt) {
      _cnt = tau(i);
      if (_cnt > cnt) {
        ans = i;
        cnt = _cnt;
      }
    }
    cout << "Between " << l << " and " << r << ", " << ans
         << " has a maximum of " << cnt << " divisors.\n";
  }
  return 0;
}
