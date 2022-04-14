#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
#define __FASTIO__
#ifdef __C_STYLE__
#include <bits/stdc++.h>
#endif
#ifdef __C_LIB__
#include <bits/stdc++.h>
#endif
#ifdef __CPP_STYLE__
#include <bits/stdc++.h>
#endif
#ifdef __CPP_LIB__
#include <bits/stdc++.h>
#endif
#ifdef __STL__
#include <bits/stdc++.h>
#endif
#ifdef __DEF__

#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
#define _replu(i, l, r) for (long unsigned int i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define _repr(i, r, l) for (int i = (r); i > (l); --i)
#define _gc getchar
#define tpn typename
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define sstream std::stringstream
#define _getch(ch) while (((ch) = gc()) != '\n' && (ch) != ' ' && (ch) != '\r')
#ifdef __C_LIB__
#define _mem(a) memset(a, 0, sizeof(a))
#define _meminf(a) memset(a, 0x3f, sizeof(a))
#define _memng(a) memset(a, 0xff, sizeof(a))
#endif
#ifdef __CPP_STYLE__
#define SYNC std::ios::sync_with_stdio(false)
#define _debug(x) std::cout << #x << " = " << x << std::endl
#else
#define _debug(type, x) printf(#x "=%" #type "\n", (x))
#endif
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
#endif
#ifndef tpn
#define tpn typename
#endif
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
#ifdef __FASTIO__
#if 0
#ifndef tpn
#define tpn typename
#endif
    template <tpn A> inline void read(A &x){
        char c;
        A neg=1;
        do{
            c=getchar();
        }while ((c<'0'||c>'9')&&c!='-');
        if (c=='-') neg=-1,c=getchar();
        x=0;
        do{
            x=(x<<3)+(x<<1)+(c^48);
            c=getchar();
        }while (c>='0'&&c<='9');
        x*=neg;
    }
    template <tpn A,tpn B> inline void read(A &a,B &b){
    read(a),read(b);}
    template <tpn A,tpn B,tpn C> inline void read(A &a,B &b,C &c){
    read(a),read(b),read(c);}
    template <tpn A,tpn B,tpn C,tpn D> inline void read(A &a,B &b,C &c,D &d){
    read(a),read(b),read(c),read(d);}
#else
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
inline void read(Type &x) {
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
}  // namespace fastIO
#endif
#endif
#define M 310
#define INF 0x3f3f3f3f
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int N = 1e7 + 5;
i128 k, mod;
std::map<i128, int> set;
inline i128 qpow(i128 a, i128 b) {
    i128 ans = 1;
    for (; b; a = a * a % mod, b >>= 1)
        if (b & 1) ans = ans * a % mod;
    return ans;
}
inline i128 bsgs(i128 x, i128 y) {
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