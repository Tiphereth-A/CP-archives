#include <bits/stdc++.h>
#define _lowbit(x) ((x) & (-x))
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = ' ';
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
void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int N = 2e6 + 5;
int n, k;
i64 tr[N];
void add(int pos, i64 k) {
  for (; pos <= n; pos += _lowbit(pos)) tr[pos] += k;
}
i64 query(int pos) {
  i64 ans = 0;
  for (; pos; pos -= _lowbit(pos)) ans += tr[pos];
  return ans;
}
int main() {
  read(n, k);
  k = std::min(k, n - k);
  int now_pos = 1;
  i64 ans = 1;
  do {
    now_pos += k;
    ++ans;
    if (now_pos > n) {
      ans += query(n) - query(now_pos - k) + query(now_pos - n - 1);
      add(now_pos - k, 1);
      add(now_pos -= n, 1);
    } else {
      ans += query(now_pos - 1) - query(now_pos - k);
      add(now_pos - k, 1);
      add(now_pos, 1);
    }
    print(ans);
  } while (now_pos != 1);
  FastIO::flush();
  return 0;
}
