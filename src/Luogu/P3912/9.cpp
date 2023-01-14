#include <cctype>
#include <cmath>
#include <cstdio>
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
bool a[100000001], *pos = a + 2;
int n, num = 0;
int main() {
  read(n);
  int ans = n, sqrt_n = sqrt(n);
  for (rint i = 2; i <= sqrt_n; ++i) {
    if (*(pos++)) continue;
    for (rint j = i * 2; j <= n; j += i) {
      if (!a[j]) ans--;
      a[j] = 1;
    }
  }
  print(ans - 1);
  return 0;
}
