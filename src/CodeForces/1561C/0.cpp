#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
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
struct {
  int id, minp;
} a[N];
int k[N];
bool judge(int x) {}
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n, a_, now) {
    a[i].id = i;
    cin >> k[i];
    a[i].minp = 0;
    _for(j, -1, k[i] - 2) {
      cin >> a_;
      chkmax(a[i].minp, a_ - j);
    }
  }
  sort(a + 1, a + n + 1, [](const auto &lhs, const auto &rhs) -> bool {
    return lhs.minp < rhs.minp;
  });
  int ans = a[1].minp, sum = ans;
  _for(i, 2, n) {
    if ((sum += k[a[i - 1].id]) < a[i].minp) {
      ans += a[i].minp - sum;
      sum = a[i].minp;
    }
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
