#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET;
template <typename Tp>
class BIT {
public:
  Tp tree[N];
  constexpr size_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() {}
  void modify(size_t pos, Tp val = 1) {
    for (size_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  Tp query(size_t pos) const {
    Tp ret = 0;
    for (size_t i = pos; i; i = (ptrdiff_t)i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
BIT<int> btrow, btcol;
int cntr[N], cntc[N];
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m, t, x1, y1, x2, y2) {
    cin >> t >> x1 >> y1;
    if (t == 1) {
      if (!cntr[x1]) btrow.modify(x1, 1);
      ++cntr[x1];
      if (!cntc[y1]) btcol.modify(y1, 1);
      ++cntc[y1];
    } else if (t == 2) {
      --cntr[x1];
      if (!cntr[x1]) btrow.modify(x1, -1);
      --cntc[y1];
      if (!cntc[y1]) btcol.modify(y1, -1);
    } else if (t == 3) {
      cin >> x2 >> y2;
      if (x1 > x2) swap(x1, x2);
      if (y1 > y2) swap(y1, y2);
      cout << (btrow.query(x2) - btrow.query(x1 - 1) == x2 - x1 + 1 ||
                   btcol.query(y2) - btcol.query(y1 - 1) == y2 - y1 + 1 ?
                 "Yes" :
                 "No")
           << '\n';
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
