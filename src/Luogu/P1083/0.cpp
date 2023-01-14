#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define N 1000005
namespace fastIO {
#define gc()                                                    \
  (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), \
               (iS == iT ? EOF : *iS++)) :                      \
              *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], fu[110], c;
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
int n, m, r[N], s[N], t[N], d[N], diff[N];
bool judge(int x) {
  mem(diff);
  _for(i, 1, x) {
    diff[s[i]] += d[i];
    diff[t[i] + 1] -= d[i];
  }
  int now = 0;
  _for(i, 1, n) {
    now += diff[i];
    if (now > r[i]) return 0;
  }
  return 1;
}
int main() {
  read(n);
  read(m);
  _for(i, 1, n) read(r[i]);
  _for(i, 1, m) {
    read(d[i]);
    read(s[i]);
    read(t[i]);
  }
  if (judge(m)) {
    puts("0");
    return 0;
  }
  int l = 1, r = m;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (judge(mid)) l = mid + 1;
    else r = mid;
  }
  printf("-1\n%d", l);
  return 0;
}
