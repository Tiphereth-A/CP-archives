#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
#define __FASTIO__
#ifdef __C_STYLE__
#include <cstdio>
#endif
#ifdef __C_LIB__
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#endif
#ifdef __CPP_STYLE__
#include <iostream>
#endif
#ifdef __CPP_LIB__
#include <fstream>
#include <iomanip>
#include <string>
#endif
#ifdef __STL__
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#endif
#ifdef __STD__
using namespace std;
#endif
#ifdef __DEF__
#define rg register
#define rgi register int
#define il inline
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define rep(i, l, r) for (register int i = (l); i < (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define gc getchar
#define tpn typename
#ifdef __C_LIB__
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 0x3f, sizeof(a))
#define memng(a) memset(a, 0xff, sizeof(a))
#endif
#ifdef __CPP_STYLE__
#define dbg(x) cout << #x << " = " << x << endl
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef double db;
typedef long double ldb;
#endif
#ifndef tpn
#define tpn typename
#endif
template <tpn A>
inline A Max(const A& x, const A& y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A& x, const A& y) {
    return x < y ? x : y;
}
template <tpn A>
inline void Swap(A& x, A& y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A& x) {
    return x > 0 ? x : -x;
}
#ifdef __FASTIO__
#if 1
#ifndef tpn
#define tpn typename
#endif
template <tpn A>
inline void read(A& x) {
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
inline void read(A& a, B& b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A& a, B& b, C& c) {
    read(a), read(b), read(c);
}
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A& a, B& b, C& c, D& d) {
    read(a), read(b), read(c), read(d);
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
#endif
#endif
#define M 310
#define INF 0x3f3f3f3f
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int N = 1e7 + 5;
int n, m;
int tr[N];
#define lowbit(x) (x) & (-(x))
il void add(int s, int t) {
    for (rg int i = s; i <= n; i += lowbit(i)) ++tr[i];
    for (rg int i = t + 1; i <= n; i += lowbit(i)) --tr[i];
}
il i64 query(int x) {
    i64 ans = 0;
    for (rg int i = x; i; i -= lowbit(i)) ans += tr[i];
    return ans;
}
int main() {
    read(n, m);
    int f, a, b;
    fp(i, 1, m) {
        read(f, a);
        if (f)
            printf("%lld\n", query(a));
        else {
            read(b);
            add(a, b);
        }
    }
    return 0;
}