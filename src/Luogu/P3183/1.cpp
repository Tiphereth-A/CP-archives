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
}  // namespace FastIO
using FastIO::print;
using FastIO::print_h;
using FastIO::read;
const i64 M = 2e6 + 5, N = 1e6 + 5;
i64 n, m;
struct edge {
  i64 to, next;
} e[M];
i64 head[N], cnt;
void add(i64 u, i64 v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}
int in[N], out[N];
i64 f[N];
i64 dfs(i64 pos) {
  if (f[pos]) return f[pos];
  if (in[pos] && !out[pos]) return f[pos] = 1;
  for (i64 i = head[pos]; i; i = e[i].next) { f[pos] += dfs(e[i].to); }
  return f[pos];
}
int main() {
  read(n, m);
  for (i64 i = 1, x, y; i <= m; ++i) {
    read(x, y);
    add(x, y);
    ++in[y];
    ++out[x];
  }
  i64 ans = 0;
  _for(i, 1, n) {
    if (!in[i]) ans += dfs(i);
  }
  print(ans);
  FastIO::flush();
  return 0;
}
