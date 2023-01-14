#include <bits/stdc++.h>
#define _replu(i, l, r) for (long unsigned int i = (l); i < (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
namespace fastIO {
#define gc()                                                    \
  (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), \
               (iS == iT ? EOF : *iS++)) :                      \
              *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], obuff[SIZ], *oS = obuff, *oT = oS + SIZ - 1, fu[110],
                                       c;
int fr;
void out() {
  fwrite(obuff, 1, oS - obuff, stdout);
  oS = obuff;
}
template <class Type>
void read(Type &x) {
  x = 0;
  Type y = 1;
  for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc());
  c == '-' ? y = -1 : x = (c & 15);
  for (c = gc(); c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  x *= y;
}
template <class Type, typename... Args>
void read(Type &x, Args &...args) {
  read(x);
  read(args...);
}
template <class Type>
void print(Type x, char text = '\n') {
  if (x < 0) *oS++ = '-', x *= -1;
  if (x == 0) *oS++ = '0';
  while (x) fu[++fr] = x % 10 + '0', x /= 10;
  while (fr) *oS++ = fu[fr--];
  *oS++ = text;
  out();
}
}  // namespace fastIO
int n, a, b = 1, c;
int main() {
  scanf("%d", &n);
  u64 m = n * n * n;
  _replu(i, 2, m) {
    c = (a + b) % n;
    if (b == 0 && c == 1) {
      printf("%d", i - 1);
      return 0;
    }
    a = b;
    b = c;
  }
  return 0;
}
