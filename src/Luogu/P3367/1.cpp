#include <bits/stdc++.h>
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
void read() {}
void print() {}
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
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
  x = f ? -x : x;
  read(oth...);
}
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
#define read FastIO::read
#define print FastIO::print
const int MAXN = 1e4 + 5;
int fa[MAXN];
int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[fa[fa[fa[fa[fa[fa[fa[x]]]]]]]]);
}
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
  int n, m, opt, x, y;
  read(n, m);
  for (int i = 1; i <= n; i++) fa[i] = i;
  while (m--) {
    read(opt);
    if (opt & 1) {
      read(x, y);
      merge(x, y);
    } else {
      read(x, y);
      puts(find(x) == find(y) ? "Y" : "N");
    }
  }
  FastIO::flush();
  return 0;
}
