#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _mid(l, r) (((l) + (r)) >> 1)
const int N = 2e5 + 5;
int n, m, max_order, node_cnt;
int a[N], b[N], node_root[N];
struct tree {
  int val, l, r;
} seq[N << 5];
void modify(int pre, int l, int r, int &now, int p) {
  seq[now = ++node_cnt] = {seq[pre].val + 1, seq[pre].l, seq[pre].r};
  if (l == r) return;
  int mid = _mid(l, r);
  if (p <= mid) modify(seq[pre].l, l, mid, seq[now].l, p);
  else modify(seq[pre].r, mid + 1, r, seq[now].r, p);
}
int query(int node_l, int node_r, int l, int r, int k) {
  if (l == r) return l;
  int mid = _mid(l, r), tmp = seq[seq[node_r].l].val - seq[seq[node_l].l].val;
  if (k <= tmp) return query(seq[node_l].l, seq[node_r].l, l, mid, k);
  else return query(seq[node_l].r, seq[node_r].r, mid + 1, r, k - tmp);
}
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 1, n) {
    scanf("%d", a + i);
    b[i] = a[i];
  }
  std::sort(b + 1, b + n + 1);
  max_order = std::unique(b + 1, b + n + 1) - b - 1;
  _for(i, 1, n)
    modify(node_root[i - 1],
           1,
           max_order,
           node_root[i],
           std::lower_bound(b + 1, b + max_order + 1, a[i]) - b);
  int l, r, k;
  while (m--) {
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", b[query(node_root[l - 1], node_root[r], 1, max_order, k)]);
  }
  return 0;
}
