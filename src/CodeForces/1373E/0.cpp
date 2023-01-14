#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
const uint32_t OFFSET = 5;
const uint32_t N = 8e4 + OFFSET;
int __cnt[N];
constexpr auto __0 = [](int x) -> i64 {
  int d = x / 9;
  i64 ret = x % 9;
  while (d--) ret = ret * 10 + 9;
  return ret;
};
constexpr auto __1 = [](int x) -> i64 {
  if (x < 10) return x & 1 ? x / 2 : -1;
  if (x < 27)
    return x & 1 ? x < 18 ? x / 2 : (x - 17) * 5 + 8 : (x - 10) * 5 + 9;
  return x & 1 ? __0((x - 17) / 2) * 10 + 8 : __0((x - 26) / 2) * 100 + 89;
};
constexpr auto __2 = [](int x) -> i64 {
  if (x % 3) return -1;
  if (x < 27) return x / 3 - 1;
  return __0(x / 3 - 8) * 10 + 7;
};
const int __ub[10] = {
  N - 3, N - 3, N - 3, 79989, 9989, 2985, 989, 689, 291, 285};
auto solve() -> void {
  int n, k;
  cin >> n >> k;
  if (k == 0) _run_return_void(cout << __0(n) << '\n');
  if (k == 1) _run_return_void(cout << __1(n) << '\n');
  if (k == 2) _run_return_void(cout << __2(n) << '\n');
  if (k * (k + 1) / 2 > n) _run_return_void(cout << "-1\n");
  if (k * (k + 1) / 2 == n) _run_return_void(cout << "0\n");
  _for(i, 1, __ub[k], _) {
    _ = 0;
    _for(j, 0, k) _ += __cnt[i + j];
    if (_ == n) _run_return_void(cout << i << '\n');
  }
  cout << "-1\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  _for(i, 1, N - 1, _i) {
    _i = i;
    while (_i) {
      __cnt[i] += _i % 10;
      _i /= 10;
    }
  }
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
