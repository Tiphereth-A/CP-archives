#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e5 + OFFSET;
const int P = 1e9 + 1;
u64 a[N];
u64 qpow(u64 a, u64 b) {
  u64 res(1);
  for (; b; b >>= 1, (a *= a))
    if (b & 1) (res *= a);
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int n, k;
    cin >> n >> k;
    _for(i, 1, n) cin >> a[i];
    map<u64, i64> _ans, cnt;
    _ans[0] = 1;
    i64 ans = 0;
    u64 _hash = 0;
    _for(i, 1ll, n) {
      if (a[i] % k) {
        _hash += ((cnt[a[i]] + 1) % k - cnt[a[i]]) * qpow(P, a[i]);
        cnt[a[i]] = (cnt[a[i]] + 1) % k;
      }
      ans += _ans[_hash]++;
    }
    cout << ans << '\n';
  }
  return 0;
}
