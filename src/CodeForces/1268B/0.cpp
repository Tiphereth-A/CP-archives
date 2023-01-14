#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
auto solve() -> void {
  int n;
  cin >> n;
  i64 cnt1 = 0, cnt2 = 0;
  _for(i, 1, n, x) {
    cin >> x;
    cnt1 += (x + (x & i & 1)) / 2;
    cnt2 += (x + !(x & i & 1)) / 2;
  }
  cout << min(cnt1, cnt2);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
