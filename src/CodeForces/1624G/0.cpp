#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 30;
tuple<int, int, int> e[M];
int fa[N];
auto find_fa(int x) -> int {
  return x == fa[x] ? fa[x] : fa[x] = find_fa(fa[x]);
}
int main() {
  auto merge = [&](int x, int y) -> bool {
    int fx = find_fa(x), fy = find_fa(y);
    return fx == fy ? 0 : fa[fx] = fy;
  };
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int n, m;
    cin >> n >> m;
    _for(i, 1, m) cin >> get<0>(e[i]) >> get<1>(e[i]) >> get<2>(e[i]);
    int ans = (1 << K) - 1;
    _rfor(i, K - 1, 0) {
      _for(i, 1, n) fa[i] = i;
      int _ = n;
      ans ^= (1 << i);
      _for(i, 1, m)
        if ((get<2>(e[i]) | ans) == ans && merge(get<0>(e[i]), get<1>(e[i])))
          --_;
      ans ^= ((int)(_ != 1) << i);
    }
    cout << ans << '\n';
  }
  return 0;
}
