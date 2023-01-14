#include <cmath>
#include <cstdio>
#include <map>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
#define _err puts("No Solution")
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
namespace fastIO {
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
void read(A &a, B &b, C &c, D &d) {
  read(a), read(b), read(c), read(d);
}
}  // namespace fastIO
std::map<int, int> set;
int qpow(i64 a, i64 b, int mod) {
  int ans = 1;
  for (; b; a = a * a % mod, b >>= 1)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
void ex_bsgs(int x, int y, int mod) {
  if (y == 1) {
    puts("0");
    return;
  }
  set.clear();
  int cnt = 0, t = 1;
  for (int d = Gcd(x, mod); d != 1; d = Gcd(x, mod)) {
    if (y % d) {
      _err;
      return;
    }
    ++cnt;
    y /= d;
    mod /= d;
    t = 1ll * t * x / d % mod;
    if (y == t) {
      printf("%d\n", cnt);
      return;
    }
  }
  int m = sqrt(mod) + 1, s = y;
  _rep(i, 0, m) {
    set[s] = i;
    s = 1ll * s * x % mod;
  }
  int tmp = qpow(x, m, mod);
  s = 1ll * t * tmp % mod;
  _for(i, 1, m) {
    if (set.count(s)) {
      printf("%d\n", i * m - set[s] + cnt);
      return;
    }
    s = 1ll * s * tmp % mod;
  }
  _err;
}
int main() {
  int k, x, mod;
  for (;;) {
    fastIO::read(x, mod, k);
    if (k + x + mod) ex_bsgs(x % mod, k % mod, mod);
    else return 0;
  }
  return 0;
}
