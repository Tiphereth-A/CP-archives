#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 50005;
i64 c[N], cnts[N], xs[N], ys[N];
i64 now_ans;
void mov(int pos, int sgn) {
  now_ans += 2 * sgn * cnts[c[pos]] + 1;
  cnts[c[pos]] += sgn;
}
int unit;
struct Node {
  int id, l, r;
  bool operator<(Node const &x) const {
    return l / unit == x.l / unit ?
             (r == x.r ? 0 : ((l / unit) & 1) ^ (r < x.r)) :
             l < x.l;
  }
} qs[N];
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  unit = sqrt(n);
  for (int i = 1; i <= n; ++i) cin >> c[i];
  for (int i = 0; i < m; ++i) {
    qs[i].id = i;
    cin >> qs[i].l >> qs[i].r;
    ++qs[i].r;
  }
  int l = 0, r = 0;
  sort(qs, qs + m);
  for (int i = 0; i < m; ++i) {
    while (l > qs[i].l) mov(--l, 1);
    while (r < qs[i].r) mov(r++, 1);
    while (l < qs[i].l) mov(l++, -1);
    while (r > qs[i].r) mov(--r, -1);
    i64 y = qs[i].r - qs[i].l, x = now_ans - y;
    y *= y - 1;
    if (!x || !y) {
      x = 0;
      y = 1;
    } else {
      i64 g = gcd(x, y);
      x /= g;
      y /= g;
    }
    xs[qs[i].id] = x;
    ys[qs[i].id] = y;
  }
  for (int i = 0; i < m; ++i) cout << xs[i] << '/' << ys[i] << '\n';
  return 0;
}
