#include <bits/stdc++.h>
const int N = 2e5 + 5;
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
int n, m;
u64 a[N];
namespace MFS {
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
}  // namespace MFS
using namespace MFS;
namespace BIT {
#define _lowbit(i) ((i) & -(i))
u64 bit[N];
void add(int x, u64 k) {
  for (int i = x; i <= n; i += _lowbit(i)) bit[i] += k;
}
u64 query(int x) {
  u64 ans = 0;
  for (int i = x; i; i -= _lowbit(i)) ans += bit[i];
  return ans;
}
}  // namespace BIT
using namespace BIT;
int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
    read(a[i]);
    add(i, a[i]);
  }
  fa[n + 1] = n + 1;
  read(m);
  for (int k, l, r, i = 1; i <= m; ++i) {
    read(k, l, r);
    if (l > r) l ^= r ^= l ^= r;
    if (k) print(query(r) - query(l - 1));
    else
      for (int i = l; i <= r; i = (find(i) == i) ? (i + 1) : fa[i]) {
        int t = sqrt(a[i]);
        add(i, t - a[i]);
        a[i] = t;
        fa[i] = (a[i] <= 1) ? i + 1 : i;
      }
  }
ex:
  FastIO::flush();
  return 0;
}
