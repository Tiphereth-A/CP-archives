#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int h[N], ans[N];
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> h[i];
  ans[1] = ans[n] = 1;
  _for(i, 2, n - 1) ans[i] = min(ans[i - 1] + 1, h[i]);
  _rfor(i, n - 1, 2) ans[i] = min(ans[i + 1] + 1, ans[i]);
  int final_ans = 0;
  _for(i, 1, n) chkmax(final_ans, ans[i]);
  cout << final_ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
