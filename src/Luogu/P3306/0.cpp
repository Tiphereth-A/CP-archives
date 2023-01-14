#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
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
int p;
std::map<int, int> list;
int qpow(i64 a, i64 b) {
  i64 ans = 1;
  for (; b; a = a * a % p, b >>= 1)
    if (b & 1) ans = ans * a % p;
  return ans;
}
i64 bsgs(int x, int y) {
  if (x == 0 && y == 0) return 0;
  if (x == 0) return -1;
  list.clear();
  int m = sqrt(p) + 1, s = y;
  _rep(i, 0, m) {
    if (!list.count(s)) list[s] = i;
    s = 1ll * s * x % p;
  }
  int tmp = qpow(x, m);
  s = 1;
  _for(i, 1, m + 1) {
    s = 1ll * s * tmp % p;
    if (list.count(s)) return 1ll * i * m - list[s] + 1;
  }
  return -1;
}
int main() {
  int a, b, x, t, n, y;
  scanf("%d", &n);
  while (n--) {
    scanf("%d%d%d%d%d", &p, &a, &b, &x, &t);
    if (x == t) {
      puts("1");
      continue;
    }
    if (a == 0) {
      printf("%d\n", b == t ? 2 : -1);
      continue;
    }
    if (a == 1) {
      if (b == 0) {
        puts("-1");
        continue;
      }
      y = (t - x + p) % p;
      printf("%lld\n", 1ll * y * qpow(b, p - 2) % p + 1);
      continue;
    }
    x %= p;
    a %= p;
    b %= p;
    t %= p;
    y = 1ll * (1ll * (a - 1) * t % p + b) % p *
        qpow(1ll * (a - 1) * x % p + b, p - 2) % p;
    printf("%lld\n", bsgs(a, y));
  }
  return 0;
}
