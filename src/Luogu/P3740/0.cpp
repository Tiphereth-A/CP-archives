#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (auto i = (r); i >= (l); --i)
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
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
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int M = 1e3 + 5;
const int N = 1e7 + 5;
int n, m;
bool tr[N << 2];
void push_up(int p) { tr[p] = tr[_lch] & tr[_rch]; }
int update(int L, int R, int p = 1, int l = 1, int r = n) {
  if (tr[p]) return 0;
  if (L <= l && r <= R) return tr[p] = 1;
  int mid = _mid(l, r), ans = 0;
  if (mid >= L) ans |= update(L, R, _lch, l, mid);
  if (mid < R) ans |= update(L, R, _rch, mid + 1, r);
  push_up(p);
  return ans;
}
struct node {
  int l, r;
} l[M];
int main() {
  read(n, m);
  _for(i, 1, m) read(l[i].l, l[i].r);
  int ans = 0;
  _rfor(i, m, 1) ans += update(l[i].l, l[i].r);
  print(ans);
  FastIO::flush();
  return 0;
}
