#include <bits/stdc++.h>
#define _lowbit(x) (1 << __builtin_ctz(x))
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
using FastIO::print;
using FastIO::print_h;
using FastIO::read;
const int M = 1e2 + 5;
const int N = 3e2 + 5;
int n, m, tr[M][N][N], a[N][N];
void modify(int color, int x, int y, int k) {
  for (int i = x; i <= n; i += _lowbit(i))
    for (int j = y; j <= m; j += _lowbit(j)) tr[color][i][j] += k;
}
int query(int color, int x, int y) {
  int ans = 0;
  for (int i = x; i; i -= _lowbit(i))
    for (int j = y; j; j -= _lowbit(j)) ans += tr[color][i][j];
  return ans;
}
int main() {
  read(n, m);
  for (int i = 1, tmp; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      read(tmp);
      modify(a[i][j] = tmp, i, j, 1);
    }
  int q;
  read(q);
  for (int i = 1, o, x1, x2, y1, y2, c; i <= q; ++i) {
    read(o);
    if (o & 1) {
      read(x1, y1, c);
      modify(a[x1][y1], x1, y1, -1);
      modify(a[x1][y1] = c, x1, y1, 1);
    } else {
      read(x1, x2, y1, y2, c);
      print(query(c, x2, y2) - query(c, x2, y1 - 1) - query(c, x1 - 1, y2) +
            query(c, x1 - 1, y1 - 1));
    }
  }
ex:
  FastIO::flush();
  return 0;
}
