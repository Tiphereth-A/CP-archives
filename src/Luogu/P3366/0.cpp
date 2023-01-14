#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
struct graph {
  int x, y, z;
  bool operator<(const graph &a) { return z < a.z; }
} g[200005];
int pre[5005];
int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
int main() {
  int n, m, cnt = 0, ans = 0, fx, fy;
  fastIO::read(n, m);
  _for(i, 1, m) fastIO::read(g[i].x, g[i].y, g[i].z);
  _for(i, 1, n) pre[i] = i;
  std::sort(g + 1, g + m + 1);
  _for(i, 1, m) {
    if (cnt == n - 1) break;
    fx = find(g[i].x), fy = find(g[i].y);
    if (fx != fy) {
      ans += g[i].z;
      pre[fx] = fy;
      ++cnt;
    }
  }
  if (cnt < n - 1) puts("orz");
  else fastIO::print(ans);
  return 0;
}
