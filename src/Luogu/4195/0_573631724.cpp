#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
#define __FASTIO__
#define __OPTMIZE__
#define __FUNC__
#ifdef __OPTMIZE__
#endif
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
#define _pc putchar
#define tpn typename
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define sstream std::stringstream
#define _getch(ch) while (((ch) = gc()) != '\n' && (ch) != ' ' && (ch) != '\r')
#define _err puts("No Solution")
#ifdef __C_LIB__
#define _mem(a) memset(a, 0, sizeof(a))
#define _meminf(a) memset(a, 0x3f, sizeof(a))
#define _memng(a) memset(a, 0xff, sizeof(a))
#endif
#ifdef __CPP_STYLE__
#define SYNC std::ios::sync_with_stdio(false)
#define _debug(x) std::cout << #x << " = " << x << std::endl
#else
#define _debug(type, x) printf(#x "=%" type "\n", (x))
#endif
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
#endif
#ifdef __FUNC__
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
template <tpn A>
inline A Gcd(A x, A y) { return !y ? x : Gcd(y, x % y); }
#endif
#ifdef __FASTIO__
#if 1
#ifndef tpn
#define tpn typename
#endif
namespace fastIO {
template <tpn A>
inline void read(A &x) {
    char c;
    A neg = 1;
    do {
        c = getchar();
    } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') neg = -1, c = getchar();
    x = 0;
    do {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    } while (c >= '0' && c <= '9');
    x *= neg;
}
template <tpn A, tpn B>
inline void read(A &a, B &b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A &a, B &b, C &c) {
    read(a), read(b), read(c);
}
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A &a, B &b, C &c, D &d) {
    read(a), read(b), read(c), read(d);
}
}  // namespace fastIO
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
    x = 0;
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
    if (x < 0) *oS++ = '-', x *= -1;
    if (x == 0) *oS++ = '0';
    while (x) fu[++fr] = x % 10 + '0', x /= 10;
    while (fr) *oS++ = fu[fr--];
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
std::map<int, int> set;
inline int qpow(i64 a, i64 b, int mod) {
    int ans = 1;
    for (; b; a = a * a % mod, b >>= 1)
        if (b & 1) ans = ans * a % mod;
    return ans;
}
inline void ex_bsgs(int x, int y, int mod) {
    if (y == 1) {
        puts("0");
        return;
    }
    set.clear();
    int cnt = 0, t = 1;
    for (int d = Gcd(x, mod); d != 1; d = Gcd(x, mod)) {
        if (y % d) {
            _err;
            return;
        }
        ++cnt;
        y /= d;
        mod /= d;
        t = 1ll * t * x / d % mod;
        if (y == t) {
            printf("%d\n", cnt);
            return;
        }
    }
    int m = sqrt(mod) + 1, s = y;
    _rep(i, 0, m) {
        set[s] = i;
        s = 1ll * s * x % mod;
    }
    int tmp = qpow(x, m, mod);
    s = t;
    _for(i, 1, m) {
        s = 1ll * s * tmp % mod;
        if (set.count(s)) {
            printf("%d\n", i * m - set[s] + cnt);
            return;
        }
    }
    _err;
}
int main() {
    int k, x, mod;
    for (fastIO::read(x, mod, k); k + x + mod;) {
        ex_bsgs(x % mod, k % mod, mod);
        fastIO::read(x, mod, k);
    }
    return 0;
}