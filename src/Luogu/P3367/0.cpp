#include <bits/stdc++.h>
#define M 10005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define merge(x, y) pre[find(x)] = find(y)
int pre[M];
namespace fastIO {
#define gc()                                                    \
  (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), \
               (iS == iT ? EOF : *iS++)) :                      \
              *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], c;
int fr;
template <class Type>
void read(Type &x) {
  Type y = 1;
  for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc());
  c == '-' ? y = -1 : x = (c & 15);
  for (c = gc(); c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  x *= y;
}
}  // namespace fastIO
using namespace fastIO;
int find(int x) { return pre[x] == x ? x : pre[x] = find(pre[x]); }
int main() {
  int n, m;
  read(n);
  read(m);
  _for(i, 1, n) pre[i] = i;
  _for(i, 1, m) {
    int z, x, y;
    read(z);
    read(x);
    read(y);
    (z & 1) ? merge(x, y) : puts((find(x) == find(y)) ? "Y" : "N");
  }
  return 0;
}
