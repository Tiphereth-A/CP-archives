#include <bits/stdc++.h>
#define rint int
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
template <typename T>
void print(T x) {
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int N = 1e8 + 5;
bool vis[N];
int n, prime[N], cnt_prime;
int main() {
  read(n);
  for (rint i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt_prime] = i;
    for (rint j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  print(cnt_prime);
  return 0;
}
