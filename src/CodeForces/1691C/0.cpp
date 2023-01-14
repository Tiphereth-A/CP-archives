#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _all(a) (a).begin(), (a).end()
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
i64 sum[N];
auto solve() -> void {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  auto tot1 = count_if(_all(s), [](const char ch) { return ch & 1; });
  if (tot1 == 0) _run_return_void(cout << "0\n");
  int cnt = 0;
  auto ends = s.rbegin();
  for (auto it = s.rbegin(); it != s.rend(); ++it) {
    if (*it & 1) _run_break(ends = it);
    ++cnt;
  }
  int cnt2 = 0;
  auto ends2 = s.begin();
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it & 1) _run_break(ends2 = it);
    ++cnt2;
  }
  if (tot1 == 1) {
    if (k >= cnt) _run_return_void(cout << "1\n");
    if (k >= cnt2) _run_return_void(cout << "10\n");
    _run_return_void(cout << "11\n");
  }
  i64 ans = 11 * tot1;
  if (k >= cnt) {
    k -= cnt;
    ans -= 10;
  }
  if (k >= cnt2) {
    k -= cnt2;
    --ans;
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
