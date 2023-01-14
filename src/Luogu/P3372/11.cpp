#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
#define _line(l, r) ((r) - (l) + 1)
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
void read() {}
void print() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  int f = 0;
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  if (f) x = -x;
  read(oth...);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T, typename... T2>
void print(T x, T2... oth) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
  print(oth...);
}
template <typename T>
void print_h(T x, char h) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = h;
}
void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
#define print_h FastIO::print_h
const int N = 1e6 + 5;
int n, m;
i64 a[N];
struct node {
  i64 sum, lazy;
  node operator+=(node a) {
    sum += a.sum;
    lazy += a.lazy;
    return *this;
  }
} t[N << 2];
void push_up(int p) { t[p].sum = t[_lch].sum + t[_rch].sum; }
void push_down(int p, int lenth_l, int lenth_r) {
  t[_lch] += {t[p].lazy * lenth_l, t[p].lazy};
  t[_rch] += {t[p].lazy * lenth_r, t[p].lazy};
  t[p].lazy = 0;
}
void build(int p = 1, int l = 1, int r = n) {
  if (l == r) {
    t[p].sum = a[l];
    return;
  }
  int mid = _mid(l, r);
  build(_lch, l, mid);
  build(_rch, mid + 1, r);
  push_up(p);
}
void update(int L, int R, i64 k, int p = 1, int l = 1, int r = n) {
  if (L <= l && r <= R) {
    t[p] += {k * _line(l, r), k};
    return;
  }
  int mid = _mid(l, r);
  push_down(p, _line(l, mid), _line(mid + 1, r));
  if (mid >= L) update(L, R, k, _lch, l, mid);
  if (mid < R) update(L, R, k, _rch, mid + 1, r);
  push_up(p);
}
i64 query(int L, int R, int p = 1, int l = 1, int r = n) {
  if (L <= l && r <= R) return t[p].sum;
  int mid = _mid(l, r);
  i64 ans = 0;
  push_down(p, _line(l, mid), _line(mid + 1, r));
  if (mid >= L) ans += query(L, R, _lch, l, mid);
  if (mid < R) ans += query(L, R, _rch, mid + 1, r);
  return ans;
}
int main() {
  read(n, m);
  _for(i, 1, n) read(a[i]);
  build();
  int op, x, y;
  i64 k;
  _for(i, 1, m) {
    read(op, x, y);
    if (op & 1) {
      read(k);
      update(x, y, k);
    } else print(query(x, y));
  }
  FastIO::flush();
  return 0;
}
