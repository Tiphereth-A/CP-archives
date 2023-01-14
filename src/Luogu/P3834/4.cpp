#include <bits/stdc++.h>
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
struct Query {
  int i, l, r, k;
};
template <typename Tp>
class BIT {
protected:
  std::vector<Tp> tree;
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  explicit BIT(size_t sz): tree(sz) {}
  void reset(size_t sz) { tree.resize(sz, 0); }
  void modify(ptrdiff_t pos, Tp val = 1) {
    if (pos < 1) return;
    pos = std::clamp(pos, ptrdiff_t(1), ptrdiff_t(tree.size()) - 1);
    for (ptrdiff_t i = pos; i < ptrdiff_t(tree.size()); i += lowbit(i))
      tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    if (pos < 1) return 0;
    pos = std::clamp(pos, ptrdiff_t(1), ptrdiff_t(tree.size()) - 1);
    for (ptrdiff_t i = pos; i; i = i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
Query s[200005], t1[200005], t2[200005];
int n, m, cnt, pos, p[200005], ans[200005];
pair<int, int> a[200005];
BIT<int> tr(200005);
void add(int x, int y) { tr.modify(x, y); }
int sum(int x) { return tr.query(x); }
void overall_binary(int l, int r, int ql, int qr) {
  if (l > r) return;
  if (ql == qr) {
    for (int i = l; i <= r; i++) ans[s[i].i] = ql;
    return;
  }
  int cnt1 = 0, cnt2 = 0, mid = (ql + qr) >> 1;
  while (pos <= n - 1 && a[pos + 1].first <= mid)
    add(a[pos + 1].second, 1), ++pos;
  while (pos >= 1 && a[pos].first > mid) add(a[pos].second, -1), --pos;
  for (int i = l; i <= r; i++) {
    int now = sum(s[i].r) - sum(s[i].l - 1);
    if (s[i].k <= now) t1[++cnt1] = s[i];
    else t2[++cnt2] = s[i];
  }
  for (int i = 1; i <= cnt1; i++) s[l + i - 1] = t1[i];
  for (int i = 1; i <= cnt2; i++) s[l + cnt1 + i - 1] = t2[i];
  overall_binary(l, l + cnt1 - 1, ql, mid);
  overall_binary(l + cnt1, r, mid + 1, qr);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i].first);
    a[i].second = i;
    p[++cnt] = a[i].first;
  }
  sort(a + 1, a + n + 1);
  sort(p + 1, p + n + 1);
  cnt = unique(p + 1, p + n + 1) - p - 1;
  for (int i = 1; i <= n; i++)
    a[i].first = lower_bound(p + 1, p + cnt + 1, a[i].first) - p;
  for (int i = 1; i <= m; ++i) {
    s[i].i = i;
    scanf("%d%d%d", &s[i].l, &s[i].r, &s[i].k);
  }
  overall_binary(1, m, 1, cnt);
  for (int i = 1; i <= n; i++) printf("%d\n", p[ans[i]]);
  return 0;
}
