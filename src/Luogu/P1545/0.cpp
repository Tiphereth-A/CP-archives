#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
struct segtree {
  vector<int> tr;
  segtree(int n): tr((n + 1) * 4) { init(1, 1, n); }
  void init(int p, int l, int r) {
    tr[p] = inf;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    init(p * 2, l, mid);
    init(p * 2 + 1, mid + 1, r);
  }
  void modify(int pos, int v, int p, int l, int r) {
    if (l == r) {
      tr[p] = v;
      return;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid) modify(pos, v, p * 2, l, mid);
    else modify(pos, v, p * 2 + 1, mid + 1, r);
    tr[p] = min(tr[p * 2], tr[p * 2 + 1]);
  }
  int query(int ql, int qr, int p, int l, int r) {
    if (ql <= l && r <= qr) return tr[p];
    int mid = l + (r - l) / 2;
    int ret = inf;
    if (ql <= mid) ret = min(ret, query(ql, qr, p * 2, l, mid));
    if (mid < qr) ret = min(ret, query(ql, qr, p * 2 + 1, mid + 1, r));
    return ret;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, l, a, b;
  cin >> n >> l >> a >> b;
  vector<bool> vis(l + 1);
  {
    vector<int> d(l + 1);
    for (int i = 1, s, e; i <= n; ++i) {
      cin >> s >> e;
      ++d[s + 1];
      --d[e];
    }
    for (int i = 1; i <= l; ++i) {
      if ((d[i] += d[i - 1]) > 0) vis[i] = 1;
    }
  }
  segtree t(l + 1);
  t.modify(1, 0, 1, 1, l + 1);
  for (int i = 2 * a; i <= l; i += 2)
    if (!vis[i]) {
      int ql = max(0, i - b * 2), qr = i - a * 2;
      t.modify(i + 1, t.query(ql + 1, qr + 1, 1, 1, l + 1) + 1, 1, 1, l + 1);
    }
  int ans = t.query(l + 1, l + 1, 1, 1, l + 1);
  cout << (ans >= inf ? -1 : ans);
  return 0;
}
