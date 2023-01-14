#include <bits/stdc++.h>
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
const int N = 1e7 + 5;
int n, a[N], f[65536], b[N];
void radix_sort() {
  for (int i = 1; i <= n; ++i) ++f[a[i] & 65535];
  for (int i = 0; i < 65536; ++i) f[i] += f[i - 1];
  for (int i = n; i; --i) b[f[a[i] & 65535]--] = a[i];
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= n; ++i) ++f[b[i] >> 16 & 65535];
  for (int i = 0; i < 65536; ++i) f[i] += f[i - 1];
  for (int i = n; i; --i) a[f[b[i] >> 16 & 65535]--] = b[i];
  return;
}
int main() {
  read(n);
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    if (a[i] < 0) ++cnt;
  }
  radix_sort();
  for (int i = n - cnt + 1; i <= n; ++i) print(a[i]);
  for (int i = 1; i <= n - cnt; ++i) print(a[i]);
  FastIO::flush();
  return 0;
}
