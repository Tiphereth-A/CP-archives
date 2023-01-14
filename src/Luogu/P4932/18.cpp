#include <bits/stdc++.h>
using u64 = uint64_t;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
int In, Ia, Ib, Ic, Id;
u64 pre, cnt[2];
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
int main() {
  read(In);
  read(Ia);
  read(Ib);
  read(Ic);
  read(Id);
  read(pre);
  Ia %= Id;
  Ib %= Id;
  Ic %= Id;
  _for(i, 1, In)
    (Id > 937500000) ?
      ++cnt[__builtin_popcount(pre = (((Ia * pre + Ib) % Id * pre + Ic) % Id)) &
            1] :
      ++cnt[__builtin_popcount(pre = (((Ia * pre + Ib) * pre + Ic) % Id)) & 1];
  printf("%llu", cnt[0] * cnt[1]);
  return 0;
}
