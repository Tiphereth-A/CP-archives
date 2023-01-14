#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
struct segtree {
#define ls(p) tr[(p) * 2]
#define rs(p) tr[(p) * 2 + 1]
  struct Node {
    i64 minfh, minf, tag;
  };
  vector<Node> tr;
  segtree(int n): tr((n + 1) * 4) { init(1, 1, n); }
  void pu(int p) {
    tr[p].minfh = min(ls(p).minfh, rs(p).minfh);
    tr[p].minf = min(ls(p).minf, rs(p).minf);
  }
  void pd(int p) {
    if (tr[p].tag == inf) return;
    ls(p).minfh = ls(p).minf + tr[p].tag;
    rs(p).minfh = rs(p).minf + tr[p].tag;
    ls(p).tag = rs(p).tag = tr[p].tag;
    tr[p].tag = inf;
  }
  void init(int p, int l, int r) {
    tr[p] = {inf, inf, inf};
    if (l == r) return;
    int mid = l + (r - l) / 2;
    init(p * 2, l, mid);
    init(p * 2 + 1, mid + 1, r);
  }
  void update(int ql, int qr, i64 v, int p, int l, int r) {
    if (ql <= l && r <= qr) {
      tr[p] = {tr[p].minf + v, tr[p].minf, v};
      return;
    }
    int mid = l + (r - l) / 2;
    pd(p);
    if (ql <= mid) update(ql, qr, v, p * 2, l, mid);
    if (mid < qr) update(ql, qr, v, p * 2 + 1, mid + 1, r);
    pu(p);
  }
  void modify(int pos, i64 v, int p, int l, int r) {
    if (l == r) {
      tr[p] = {inf, v, tr[p].tag};
      return;
    }
    int mid = l + (r - l) / 2;
    pd(p);
    if (pos <= mid) modify(pos, v, p * 2, l, mid);
    else modify(pos, v, p * 2 + 1, mid + 1, r);
    pu(p);
  }
  i64 query(int ql, int qr, int p, int l, int r) {
    if (ql <= l && r <= qr) return tr[p].minfh;
    int mid = l + (r - l) / 2;
    i64 ret = inf;
    pd(p);
    if (ql <= mid) ret = min(ret, query(ql, qr, p * 2, l, mid));
    if (mid < qr) ret = min(ret, query(ql, qr, p * 2 + 1, mid + 1, r));
    return ret;
  }
#undef ls
#undef rs
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, l;
  cin >> n >> l;
  vector<i64> h(n + 1), w;
  for (int i = 1; i <= n; ++i) cin >> h[i];
  w = h;
  vector<i64> sumw(n + 1);
  partial_sum(w.begin(), w.end(), sumw.begin());
  vector<int> stk{1}, pre(n + 1);
  for (int i = 2; i <= n; ++i) {
    while (!stk.empty() && h[i] > h[stk.back()]) stk.pop_back();
    if (!stk.empty()) pre[i] = stk.back();
    stk.push_back(i);
  }
  segtree tr(n);
  vector<i64> f(n + 1);
  for (int i = 1; i <= n; ++i) {
    tr.modify(i, f[i - 1], 1, 1, n);
    if (pre[i] + 1 <= i) tr.update(pre[i] + 1, i, h[i], 1, 1, n);
    int d = lower_bound(sumw.begin(), sumw.begin() + i + 1, sumw[i] - l) -
            sumw.begin();
    if (d < i) f[i] = tr.query(d + 1, i, 1, 1, n);
  }
  cout << f[n] << '\n';
  return 0;
}
