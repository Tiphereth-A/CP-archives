#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
typedef __int128 i128;
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
  Type y = 1;
  for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc());
  c == '-' ? y = -1 : x = (c & 15);
  for (c = gc(); c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  x *= y;
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
i128 k, mod;
std::map<i128, int> set;
i128 qpow(i128 a, i128 b) {
  i128 ans = 1;
  for (; b; a = a * a % mod, b >>= 1)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
i128 bsgs(i128 x, i128 y) {
  set.clear();
  if (x == 0 && y == 0) return 0;
  if (x == 0) return -1;
  i128 m = (i128)sqrt((double)mod) + 1, s = y;
  _rep(i, 0, m) {
    if (!set[s]) set[s] = i;
    s = s * x % mod;
  }
  i128 tmp = qpow(x, m);
  s = 1;
  _for(i, 1, m + 1) {
    s = s * tmp % mod;
    if (set.count(s)) return i * m - set[s];
  }
  return -1;
}
int main() {
  fastIO::read(k);
  fastIO::read(mod);
  fastIO::print(bsgs(10 % mod, (9 * k + 1) % mod));
  return 0;
}
