#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _mid(l, r) (((l) + (r)) >> 1)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
template <typename Type>
void read_digit(Type &x) {
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
  x = f ? -ret : ret;
}
template <typename A, typename B>
void read_digit(A &a, B &b) {
  read_digit(a), read_digit(b);
}
template <typename A, typename B, typename C>
void read_digit(A &a, B &b, C &c) {
  read_digit(a), read_digit(b), read_digit(c);
}
template <typename A, typename B, typename C, typename D>
void read_digit(A &a, B &b, C &c, D &d) {
  read_digit(a), read_digit(b), read_digit(c), read_digit(d);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename Type>
void print_digit(Type x) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
}
}  // namespace FastIO
#define read FastIO::read_digit
#define print FastIO::print_digit
const int N = 2e5 + 5;
int n, m;
int a[N], b[N], b_len;
struct chman_tree {
  int val, l, r;
} tree[N << 5];
int root[N << 5], node_cnt;
#define PRE tree[pre]
#define PREL tree[L]
#define PRER tree[R]
#define NOW tree[now]
void modify(int pre, int l, int r, int &now, int pos) {
  tree[now = ++node_cnt] = {PRE.val + 1, PRE.l, PRE.r};
  if (l == r) return;
  int mid = _mid(l, r);
  if (pos <= mid) modify(PRE.l, l, mid, NOW.l, pos);
  else modify(PRE.r, mid + 1, r, NOW.r, pos);
}
int query(int L, int R, int l, int r, int k) {
  if (l == r) return l;
  int mid = _mid(l, r), tmp = tree[PRER.l].val - tree[PREL.l].val;
  if (k <= tmp) return query(PREL.l, PRER.l, l, mid, k);
  else return query(PREL.r, PRER.r, mid + 1, r, k - tmp);
}
int main() {
  read(n, m);
  _for(i, 1, n) {
    read(a[i]);
    b[i] = a[i];
  }
  std::sort(b + 1, b + n + 1);
  b_len = std::unique(b + 1, b + n + 1) - b - 1;
  _for(i, 1, n)
    modify(root[i - 1],
           1,
           b_len,
           root[i],
           std::lower_bound(b + 1, b + b_len + 1, a[i]) - b);
  int l, r, k;
  while (m--) {
    read(l, r, k);
    print(b[query(root[l - 1], root[r], 1, b_len, k)]);
  }
  FastIO::flush();
  return 0;
}
