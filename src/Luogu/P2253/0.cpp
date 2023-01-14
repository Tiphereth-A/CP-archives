#include <algorithm>
#include <cctype>
#include <cstdio>
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
using std::max;
int n, m;
struct node_sgt {
  int l, r, m;
} tr[N << 2];
bool a[N];
void push_up(int p, int l, int r, int mid) {
  if ((tr[p].l = tr[_lch].l) == mid - l + 1 && (a[mid] ^ a[mid + 1]))
    tr[p].l += tr[_rch].l;
  if ((tr[p].r = tr[_rch].r) == r - mid && (a[mid] ^ a[mid + 1]))
    tr[p].r += tr[_lch].r;
  tr[p].m = max(tr[_lch].m, tr[_rch].m);
  if (a[mid] ^ a[mid + 1]) tr[p].m = max(tr[p].m, tr[_lch].r + tr[_rch].l);
}
void init(int p = 1, int l = 1, int r = n) {
  if (l == r) {
    tr[p] = {1, 1, 1};
    return;
  }
  int mid = _mid(l, r);
  init(_lch, l, mid);
  init(_rch, mid + 1, r);
  push_up(p, l, r, mid);
}
void modify(int pos, int p = 1, int l = 1, int r = n) {
  if (l == r) {
    a[l] = !a[l];
    return;
  }
  int mid = _mid(l, r);
  if (mid >= pos) modify(pos, _lch, l, mid);
  else modify(pos, _rch, mid + 1, r);
  push_up(p, l, r, mid);
}
int main() {
  read(n, m);
  init();
  for (int i = 1, tmp; i <= m; ++i) {
    read(tmp);
    modify(tmp);
    print(max(tr[1].m, max(tr[1].r, tr[1].l)));
  }
  FastIO::flush();
  return 0;
}
