#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
char getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
template <class T, typename std::enable_if<is_signed_v<T>>::type * = nullptr>
void read(T &x) {
  int f = x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) { x = x * 10 + (ch & 0x0f), ch = getc(); }
  if (f) x = -x;
}
template <class T, typename std::enable_if<is_unsigned_v<T>>::type * = nullptr>
void read(T &x) {
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) ch = getc();
  while (isdigit(ch)) { x = x * 10 + (ch & 0x0f), ch = getc(); }
}
template <
  typename T,
  typename... T2,
  typename std::enable_if<is_signed_v<T> || is_unsigned_v<T>>::type * = nullptr>
void read(T &x, T2 &...oth) {
  read(x);
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
const int N = 1e7 + 5;
uint32_t f[N];
auto solve() -> void {
  uint32_t n, m;
  read(n, m);
  _for(i, 1, n) read(f[i]);
  i64 ans = 0;
  _for(i, 1, m, x) {
    read(x);
    ans += f[x] == x ? x : 1;
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
