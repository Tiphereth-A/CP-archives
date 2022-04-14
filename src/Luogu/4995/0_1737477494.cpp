#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
#define __FASTIO__
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
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define _mid(l, r) (((l) + (r)) >> 1)
#ifdef __C_LIB__
#define _mem(a) memset(a, 0, sizeof(a))
#define _meminf(a) memset(a, 0x3f, sizeof(a))
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
#if 0
#ifndef tpn
#define tpn typename
#endif
    namespace fastIO {
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
        template <tpn A,tpn... B> inline void read(A &a,B&... b){
        read(a),read(b...);}
    }
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
template <class Type, typename... Args>
inline void read(Type &x, Args &...args) {
    read(x);
    read(args...);
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
#define INF_I32 0x7fffffff
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 500005;
const int N = 305;
const int MOD = 1000003;
int h[N];
int n;
u64 ans;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", h + i);
    std::sort(h + 1, h + n + 1, std::greater<int>());
    ans += h[1] * h[1];
    for (int i = 1, j = n; i < j; --j)
        ans += (h[i] - h[j]) * (h[i] - h[j]) + (h[++i] - h[j]) * (h[i] - h[j]);
    printf("%llu", ans);
    return 0;
}