#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
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
const int N = 1e5 + 5;
int a, b, bottle[N];
bool judge(int dis) {
  int tot = 1;
  for (int now_bottle = bottle[1], i = 2; i <= a; ++i) {
    if (bottle[i] - now_bottle >= dis) {
      now_bottle = bottle[i];
      ++tot;
    }
  }
  return tot >= b;
}
int main() {
  read(a, b);
  if (b == 1) {
    print(0);
    FastIO::flush();
    return 0;
  }
  for (int i = 1; i <= a; ++i) read(bottle[i]);
  std::sort(bottle + 1, bottle + a + 1);
  int l = 0, r = bottle[a] - bottle[1], mid = 0, ans = -1;
  while (l <= r) {
    if (judge(mid = ((r - l) >> 1) + l)) {
      l = mid + 1;
      ans = std::max(ans, mid);
    } else r = mid - 1;
  }
  print(ans);
  FastIO::flush();
  return 0;
}
