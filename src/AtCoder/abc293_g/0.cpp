#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 2e5 + 5;
i64 a[N], cnt[N], ans[N];
i64 now_ans;
void add(i64 id) {
  ++cnt[a[id]];
  if (cnt[a[id]] >= 3) now_ans += (cnt[a[id]] - 1) * (cnt[a[id]] - 2) / 2;
}
void del(i64 id) {
  if (cnt[a[id]] >= 3) now_ans -= (cnt[a[id]] - 1) * (cnt[a[id]] - 2) / 2;
  --cnt[a[id]];
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
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 0; i < m; ++i) {
    qs[i].id = i;
    cin >> qs[i].l >> qs[i].r;
    ++qs[i].r;
  }
  int l = 0, r = 0;
  sort(qs, qs + m);
  for (int i = 0; i < m; ++i) {
    while (l > qs[i].l) add(--l);
    while (r < qs[i].r) add(r++);
    while (l < qs[i].l) del(l++);
    while (r > qs[i].r) del(--r);
    ans[qs[i].id] = now_ans;
  }
  for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
  return 0;
}
