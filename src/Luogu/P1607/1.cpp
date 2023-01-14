#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
const int INF_I32 = 0x3f3f3f3f;
const int N = 5e5 + 5;
int k, n, c;
struct node {
  int m, l, r;
  bool operator<(const node &other) const {
    return r == other.r ? l > other.l : r < other.r;
  }
} line[N];
struct node_sgt {
  int val, lazy;
  node_sgt operator+=(int v) {
    val += v;
    lazy += v;
    return *this;
  }
} tr[N << 2];
void push_up(int p) { tr[p].val = std::max(tr[_lch].val, tr[_rch].val); }
void push_down(int p) {
  tr[_lch] += tr[p].lazy;
  tr[_rch] += tr[p].lazy;
  tr[p].lazy = 0;
}
void update(int L, int R, int c, int p = 1, int l = 1, int r = n) {
  if (L > r || R < l) return;
  if (L <= l && r <= R) {
    tr[p] += c;
    return;
  }
  push_down(p);
  int mid = _mid(l, r);
  update(L, R, c, _lch, l, mid);
  update(L, R, c, _rch, mid + 1, r);
  push_up(p);
}
int query(int L, int R, int p = 1, int l = 1, int r = n) {
  if (L > r || R < l) return 0;
  if (L <= l && r <= R) return tr[p].val;
  int mid = _mid(l, r);
  push_down(p);
  int ans = -INF_I32;
  ans = std::max(ans, query(L, R, _lch, l, mid));
  ans = std::max(ans, query(L, R, _rch, mid + 1, r));
  push_up(p);
  return ans;
}
int main() {
  scanf("%d%d%d", &k, &n, &c);
  _for(i, 1, k) scanf("%d%d%d", &line[i].l, &line[i].r, &line[i].m);
  std::sort(line + 1, line + k + 1);
  int ans = 0;
  _for(i, 1, k) {
    int tmp = query(line[i].l, line[i].r);
    if (tmp >= c) continue;
    int tmp_min = std::min(c - tmp, line[i].m);
    ans += tmp_min;
    update(line[i].l, line[i].r - 1, tmp_min);
  }
  printf("%d\n", ans);
  return 0;
}
