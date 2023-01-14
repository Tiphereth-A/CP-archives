#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
i64 p, p3 = -1;
i64 getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
void print() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  i64 f = 0;
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
using FastIO::print_h;
using FastIO::read;
const i64 N = 1e5 + 5;
i64 n, m, a[N];
bool judge(i64 max) {
  i64 seg = 0, now_sum = 0;
  _for(i, 1, n) {
    now_sum += a[i];
    if (now_sum >= max) {
      ++seg;
      now_sum = (now_sum > max) ? a[i] : 0;
    }
    if (seg > m) return 0;
  }
  if (now_sum) ++seg;
  return seg <= m;
}
int main() {
  read(n, m);
  i64 l = 0, r = 0, mid;
  _for(i, 1, n) {
    read(a[i]);
    r += a[i];
    l = std::max(l, a[i]);
  }
  while (l < r) {
    mid = l + (r - l) / 2;
    if (judge(mid)) r = mid;
    else l = mid + 1;
  }
  print(r);
ex:
  FastIO::flush();
  return 0;
}
