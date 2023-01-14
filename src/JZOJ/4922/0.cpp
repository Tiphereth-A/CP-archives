#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const uint32_t N = 2e3 + 5, M = 2e4 + 5;
int a[N];
i64 factor[M];
int cnt_factor;
i64 ans[N];
int main() {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  i64 sum_a = 0;
  _for(i, 1, n) sum_a += a[i];
  _for(i, 1, (int)sqrt(sum_a))
    if (sum_a % i == 0) {
      factor[++cnt_factor] = i;
      if (sum_a / i != i) factor[++cnt_factor] = sum_a / i;
    }
  _for(i, 1, cnt_factor) {
    i64 now_factor = factor[i];
    i64 sum = 0;
    unordered_map<i64, int> cnt_slice;
    int max_slice = 0;
    _for(i, 1, n)
      chkmax(max_slice, ++cnt_slice[sum = (sum + a[i]) % now_factor]);
    chkmax(ans[max_slice], now_factor);
  }
  _rfor(i, n - 1, 1) chkmax(ans[i], ans[i + 1]);
  _for(i, 1, n) cout << ans[i] << '\n';
  return 0;
}
