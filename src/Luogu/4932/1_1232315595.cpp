#include <cstdio>
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef unsigned long long u64;
int In, Ia, Ib, Ic, Id;
u64 pre, cnt[2];
namespace fastIO {
#define gc() (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], obuff[SIZ], *oS = obuff, *oT = oS + SIZ - 1, fu[110], c;
int fr;
inline void out() {
    fwrite(obuff, 1, oS - obuff, stdout);
    oS = obuff;
}
template <class Type>
inline void read(Type& x) {
    Type y = 1;
    for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc())
        ;
    c == '-' ? y = -1 : x = (c & 15);
    for (c = gc(); c >= '0' && c <= '9'; c = gc())
        x = x * 10 + (c & 15);
    x *= y;
}
template <class Type>
inline void print(Type x, char text = '\n') {
    if (x < 0)
        *oS++ = '-', x *= -1;
    if (x == 0)
        *oS++ = '0';
    while (x)
        fu[++fr] = x % 10 + '0', x /= 10;
    while (fr)
        *oS++ = fu[fr--];
    *oS++ = text;
    out();
}
} // namespace fastIO
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
    _fp(i, 1, In) cnt[__builtin_popcount(pre = (((Ia * pre + Ib) % Id * pre + Ic) % Id)) & 1]++;
    print(cnt[0] * cnt[1]);
    return 0;
}