#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
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
const int MOD = 998244353;
const u64 s[] = {
  1,        1,         3,         13,        75,        541,       4683,
  47293,    545835,    7087261,   102247563, 624388220, 140725711, 783574350,
  58167463, 197672989, 507523296, 622140839, 604776563, 768918857, 809378366};
u64 ans;
int n, m;
int main() {
  scanf("%d%d", &n, &m);
  char c[30];
  u64 tmp2;
  int tmp, clen;
  _for(i, 1, m) {
    tmp = 0;
    scanf("%s %llu", c, &tmp2);
    tmp2 %= MOD;
    clen = strlen(c);
    _rep(j, 0, clen) if (c[j] == '0')++ tmp;
    ans = (ans + s[tmp] * tmp2 % MOD * s[n - tmp] % MOD) % MOD;
  }
  printf("%llu", ans % MOD);
  return 0;
}
