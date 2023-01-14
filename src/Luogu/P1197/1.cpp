#include <bits/stdc++.h>
const int M = 4e5 + 5;
int n, m, fa[M], tar[M];
struct edge {
  int from, next, to;
} e[M];
int head[M], cnt, ans[M], tot;
bool broken[M];
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
void add(int u, int v) {
  e[++cnt] = {u, head[u], v};
  head[u] = cnt;
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if (fx != fy) {
    fa[fy] = fx;
    --tot;
  }
}
int main() {
  fastIO::read(n, m);
  for (int i = 0; i < n; ++i) fa[i] = i;
  int u, v;
  for (int i = 0; i < m; ++i) {
    fastIO::read(u, v);
    add(u, v);
    add(v, u);
  }
  fastIO::read(u);
  for (int i = 1; i <= u; ++i) {
    fastIO::read(v);
    broken[tar[i] = v] = 1;
  }
  tot = n - u;
  for (int i = 1; i <= m * 2; i += 2)
    if (!broken[e[i].from] && !broken[e[i].to]) merge(e[i].from, e[i].to);
  ans[u + 1] = tot;
  for (int i = u; i; --i) {
    int now = tar[i];
    ++tot;
    broken[now] = 0;
    for (int j = head[now]; j; j = e[j].next) {
      if (!broken[e[j].to]) merge(now, e[j].to);
    }
    ans[i] = tot;
  }
  for (int i = 1; i <= u + 1; ++i) fastIO::print(ans[i]);
  return 0;
}
