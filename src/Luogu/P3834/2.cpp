#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _mid(l, r) (((l) + (r)) >> 1)
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
int read() {
  int ret = 0, f = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    ret = ret * 10 + ch - 48;
    ch = getc();
  }
  return f ? -ret : ret;
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
void print(int x) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
}
}  // namespace FastIO
#define read() FastIO::read()
#define print(x) FastIO::print(x)
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
  n = read();
  m = read();
  _for(i, 1, n) b[i] = a[i] = read();
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
    l = read();
    r = read();
    k = read();
    print(b[query(node_root[l - 1], node_root[r], 1, max_order, k)]);
  }
  FastIO::flush();
  return 0;
}
