#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
const int N = 1e5 + 5;
int n, k;
int wood[N];
u64 sum_woods;
bool judge(u64 len) {
  u64 sum_subwoods = 0;
  _for(i, 1, n) {
    sum_subwoods += wood[i] / len;
    if (sum_subwoods >= k) return true;
  }
  return false;
}
int main() {
  read(n, k);
  _for(i, 1, n) {
    read(wood[i]);
    sum_woods += wood[i];
  }
  u64 l = 0, r = (sum_woods /= k) + 1, mid;
  while (l < r) {
    mid = ((r - l + 1) >> 1) + l;
    if (judge(mid)) l = mid;
    else r = mid - 1;
  }
  print(l);
  FastIO::flush();
  return 0;
}
