#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
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
const int N = 1000015;
const int MOD = 1000003;
int p;
struct hash {
    int list[N], head[N], next[N], id[N], top;
    inline void insert(int val, int y) {
        int k = val % MOD;
        list[++top] = val;
        id[top] = y;
        next[top] = head[k];
        head[k] = top;
    }
    inline int find(int val) {
        int k = val % MOD;
        for (int i = head[k]; ~i; i = next[i])
            if (list[i] == val) return id[i];
        return -1;
    }
} list;
inline int qpow(i64 a, i64 b) {
    i64 ans = 1;
    for (; b; a = a * a % p, b >>= 1)
        if (b & 1) ans = ans * a % p;
    return ans;
}
inline i64 bsgs(int x, int y) {
    if (x == 0) return -1;
    _memng(list.head);
    int m = sqrt(p) + 1, s = y;
    _rep(i, 0, m) {
        if (list.find(s) == -1) list.insert(s, i);
        s = 1ll * s * x % p;
    }
    int tmp = qpow(x, m);
    s = 1;
    _for(i, 1, m + 1) {
        s = 1ll * s * tmp % p;
        int tmpp = list.find(s);
        if (~tmpp) return 1ll * i * m - tmpp + 1;
    }
    return -1;
}
int main() {
    int a, b, x, t, n, y;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d%d%d%d", &p, &a, &b, &x, &t);
        if (x == t) {
            puts("1");
            continue;
        }
        if (a == 0) {
            printf("%d\n", b == t ? 2 : -1);
            continue;
        }
        if (a == 1) {
            if (b == 0) {
                puts("-1");
                continue;
            }
            y = (t - x + p) % p;
            printf("%lld\n", 1ll * y * qpow(b, p - 2) % p + 1);
            continue;
        }
        x %= p;
        a %= p;
        b %= p;
        t %= p;
        y = 1ll * (1ll * (a - 1) * t % p + b) % p * qpow(1ll * (a - 1) * x % p + b, p - 2) % p;
        printf("%lld\n", bsgs(a, y));
    }
    return 0;
}