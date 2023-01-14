#include <bits/stdc++.h>
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
using FastIO::print;
using FastIO::read;
const int N = 2e5 + 5;
struct edge {
  int x, y1, y2, state;
  bool operator<(const edge &other) const { return x < other.x; }
} e[N << 1];
int y[N << 1];
struct sgt {
  int l, r;
  int lch, rch;
  int cover;
  i64 len;
} slen[N << 3];
int n, cnt_sgt = 1;
#define _now slen[p]
#define _lch slen[_now.lch]
#define _rch slen[_now.rch]
void push_up(int p) {
  _now.len = _now.cover ? _now.r - _now.l : _lch.len + _rch.len;
}
void build(int l, int r, int p = 1) {
  _now = {y[l], y[r], 0, 0, 0, 0};
  if (r - l <= 1) return;
  int mid = _mid(l, r);
  build(l, mid, _now.lch = ++cnt_sgt);
  build(mid, r, _now.rch = ++cnt_sgt);
}
void modify(int len_p, int p = 1) {
#define _l_line e[len_p].y1
#define _r_line e[len_p].y2
#define _state_line e[len_p].state
  if (!p) return;
  if (_l_line <= _now.l && _now.r <= _r_line) {
    _now.cover += _state_line;
    push_up(p);
    return;
  }
  if (_l_line < _lch.r) modify(len_p, _now.lch);
  if (_r_line > _rch.l) modify(len_p, _now.rch);
  push_up(p);
}
int main() {
  read(n);
  for (int i = 1, x1, x2, y1, y2; i <= n; ++i) {
    read(x1, y1, x2, y2);
    e[2 * i - 1] = {x1, y[2 * i - 1] = y1, y[2 * i] = y2, 1};
    e[2 * i] = {x2, y1, y2, -1};
  }
  n <<= 1;
  std::sort(e + 1, e + n + 1);
  std::sort(y + 1, y + n + 1);
  int len_y = std::unique(y + 1, y + n + 1) - y - 1;
  build(1, len_y);
  i64 ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += slen[1].len * (e[i].x - e[i - 1].x);
    modify(i);
  }
  print(ans);
ex:
  FastIO::flush();
  return 0;
}
