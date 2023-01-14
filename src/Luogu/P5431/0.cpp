#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf;
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) { ch = getc(); }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  read(oth...);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T>
void print(T x) {
  if (p3 > 1 << 20) flush();
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int N = 5e6 + 5;
i64 qpow(i64 a, i64 b, i64 mod) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i64 n, p, k;
i64 a[N];
i64 s[N], v[N];
int main() {
  read(n, p, k);
  for (int i = 1; i <= n; ++i) read(a[i]);
  s[0] = 1;
  for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
  v[n] = qpow(s[n], p - 2, p);
  for (int i = n; i >= 1; --i) v[i - 1] = v[i] * a[i] % p;
  i64 ans = 0, _ = 1;
  for (int i = 1; i <= n; ++i)
    (ans += ((_ *= k) %= p) * v[i] % p * s[i - 1] % p) %= p;
  print(ans);
  FastIO::flush();
  return 0;
}
