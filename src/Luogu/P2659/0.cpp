#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
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
const int N = 2e6 + 5;
int n;
struct node {
  i64 val, index;
} stack[N];
i64 top, ans = 0x8000000000000000;
int main() {
  read(n);
  _for(i, 1, n) {
    int tmp;
    read(tmp);
    if (!top) {
      stack[++top] = {tmp, i};
      continue;
    }
    while (stack[top].val > tmp) {
      ans = std::max(ans, stack[top].val * (i - stack[top - 1].index - 1));
      --top;
    }
    stack[++top] = {tmp, i};
  }
  _for(i, 1, top) ans = std::max(ans, stack[i].val * (n - stack[i - 1].index));
  print(ans);
  FastIO::flush();
  return 0;
}
