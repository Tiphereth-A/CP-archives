#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define INF_I32 0x7fffffff
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
const int M = 500005;
const int N = 100005;
struct edge {
  int next, to, val;
} e[M];
int head[N], cnt;
void add(int u, int v, int val) {
  e[++cnt] = {head[u], v, val};
  head[u] = cnt;
}
int minPos[N << 2], minDis[N << 2], trM;
int n, m, s, dis[N];
void update(int pos) {
  if (minDis[_lch(pos)] < minDis[_rch(pos)]) {
    minDis[pos] = minDis[_lch(pos)];
    minPos[pos] = minPos[_lch(pos)];
  } else {
    minDis[pos] = minDis[_rch(pos)];
    minPos[pos] = minPos[_rch(pos)];
  }
}
void build() {
  for (trM = 1; trM < n + 2; trM <<= 1);
  _rep(i, trM, trM << 1) {
    minDis[i] = i - trM == s ? 0 : INF_I32;
    minPos[i] = i - trM;
  }
  _rfor(i, trM - 1, 1) update(i);
}
void modify(int pos, int k) {
  for (minDis[pos += trM] = k, pos >>= 1; pos; pos >>= 1) update(pos);
}
void dijkstra(int s) {
  build();
  _for(i, 1, n) dis[i] = INF_I32;
  dis[s] = 0;
  while (minDis[1] < INF_I32) {
    int now = minPos[1];
    int valNow = dis[now];
    modify(now, INF_I32);
    for (int i = head[now]; i; i = e[i].next) {
      int v = e[i].to, val = e[i].val;
      if (valNow + val < dis[v]) {
        dis[v] = valNow + val;
        modify(v, valNow + val);
      }
    }
  }
  _for(i, 1, n) fastIO::print(dis[i], ' ');
}
int main() {
  fastIO::read(n, m, s);
  int u, v, w;
  _for(i, 1, m) {
    fastIO::read(u, v, w);
    add(u, v, w);
  }
  dijkstra(s);
  return 0;
}
