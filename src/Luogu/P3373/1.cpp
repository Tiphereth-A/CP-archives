#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define ls p << 1
#define rs p << 1 | 1
#define Mid int m = ((r - l) >> 1) + l
typedef long long ll;
#define N 1000005
ll sum[N << 2], add[N << 2], mul[N << 2], a[N], mod;
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
using namespace fastIO;
void PushUp(int p) { sum[p] = (sum[ls] + sum[rs]) % mod; }
void PushDown(int p, int ln, int rn) {
  add[ls] = (add[ls] * mul[p] + add[p]) % mod;
  mul[ls] = (mul[ls] * mul[p]) % mod;
  sum[ls] = (sum[ls] * mul[p] + add[p] * ln) % mod;
  add[rs] = (add[rs] * mul[p] + add[p]) % mod;
  mul[rs] = mul[rs] * mul[p] % mod;
  sum[rs] = (sum[rs] * mul[p] + add[p] * rn) % mod;
  add[p] = 0;
  mul[p] = 1;
}
void Build(int l, int r, int p) {
  add[p] = 0;
  mul[p] = 1;
  if (l == r) {
    sum[p] = a[l];
    return;
  }
  Mid;
  Build(l, m, ls);
  Build(m + 1, r, rs);
  PushUp(p);
}
void Update(int L, int R, ll k, int l, int r, int p, int f) {
  if (L <= l && r <= R) {
    if (f) {
      sum[p] = (sum[p] + k * (r - l + 1)) % mod;
      add[p] = (add[p] + k) % mod;
    } else {
      sum[p] = sum[p] * k % mod;
      mul[p] = mul[p] * k % mod;
      add[p] = add[p] * k % mod;
    }
    return;
  }
  Mid;
  PushDown(p, m - l + 1, r - m);
  if (L <= m) Update(L, R, k, l, m, ls, f);
  if (R > m) Update(L, R, k, m + 1, r, rs, f);
  PushUp(p);
}
ll Query(int L, int R, int l, int r, int p) {
  if (L <= l && r <= R) return sum[p];
  Mid;
  PushDown(p, m - l + 1, r - m);
  ll ans = 0;
  if (L <= m) ans = (ans + Query(L, R, l, m, ls)) % mod;
  if (R > m) ans = (ans + Query(L, R, m + 1, r, rs)) % mod;
  return ans;
}
int main() {
  int n, m;
  read(n, m, mod);
  _for(i, 1, n) read(a[i]);
  Build(1, n, 1);
  int o, x, y;
  ll k;
  while (m--) {
    read(o, x, y);
    switch (o) {
      case 1:
        read(k);
        Update(x, y, k, 1, n, 1, 0);
        break;
      case 2:
        read(k);
        Update(x, y, k, 1, n, 1, 1);
        break;
      case 3: print(Query(x, y, 1, n, 1)); break;
    }
  }
  return 0;
}
