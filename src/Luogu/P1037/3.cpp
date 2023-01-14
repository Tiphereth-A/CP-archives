#include <cctype>
#include <cstdio>
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, ch;
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
template <typename T>
void read(T &x) {
  x = 0;
  while (ch = getc(), !isdigit(ch));
  while (isdigit(ch)) {
    (x *= 10) += ch - 48;
    ch = getc();
  }
}
template <typename T1, typename T2>
void read(T1 &x, T2 &y) {
  read(x);
  read(y);
}
template <typename T>
void print(T x) {
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
__uint128_t ans = 1, n;
bool vis[10][10];
int k, cnt[10];
int main() {
  read(n, k);
  for (int x, y; k; --k) {
    read(x, y);
    vis[x][y] = true;
  }
  for (int k = 1; k < 10; ++k)
    for (int i = 0; i < 10; ++i)
      for (int j = 1; j < 10; ++j) vis[i][j] |= vis[i][k] && vis[k][j];
  for (int i = 0; i < 10; ++i) {
    vis[i][i] = true;
    for (int j = 0; j < 10; ++j) cnt[i] += vis[i][j];
  }
  while (n) {
    ans *= cnt[n % 10];
    n /= 10;
  }
  print(ans);
  return 0;
}
