#include <bits/stdc++.h>
using namespace std;
#define _lowbit(x) (1 << __builtin_ctz(x))
typedef __int128_t i128;
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf;
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
  char ch = getc();
  while (!isdigit(ch)) { ch = getc(); }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T>
void print(T x) {
  if (p3 > 1 << 20) flush();
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
}
void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int N = 1e6 + 5;
int n;
i128 tr[N];
int a[N], rk[N], a_len;
void insert(int pos, int x) {
  for (; pos <= n; pos += _lowbit(pos)) tr[pos] += x;
}
i128 query(int x) {
  i128 ans = 0;
  for (int pos = x - 1; pos; pos -= _lowbit(pos)) ans += tr[pos];
  return ans;
}
int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(rk[i]);
    a[i] = rk[i];
  }
  sort(a + 1, a + n + 1);
  a_len = unique(a + 1, a + n + 1) - a - 1;
  for (int i = 1; i <= n; ++i)
    rk[i] = lower_bound(a + 1, a + a_len + 1, rk[i]) - a;
  i128 ans = 0;
  for (i128 i = n; i; --i) {
    ans += i * query(rk[i]);
    insert(rk[i], n - i + 1);
  }
  print(ans);
  FastIO::flush();
  return 0;
}
