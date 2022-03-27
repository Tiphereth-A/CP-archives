#define __C_STYLE__
#define __C_LIB__
#define __DEF__
#define __FUNC__
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
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#endif
#ifdef __DEF__
#define rg register
#define rgi register int
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (register int i = (l); i < (r); ++i)
#define _replu(i, l, r) for (register long unsigned int i = (l); i < (r); ++i)
#define _fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define _repr(i, r, l) for (register int i = (r); i > (l); --i)
#define _gc getchar
#define _pc putchar
#define tpn typename
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define sstream std::stringstream
#define _err puts("This puzzle has no final configuration.")
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define _mid(l, r) (((l) + (r)) >> 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbitll(x) (1 << __builtin_ctzll(x))
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
typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
#endif
#ifdef __FUNC__
#ifndef tpn
#define tpn typename
#endif
template <tpn A>
inline A Max(const A& x, const A& y) { return x > y ? x : y; }
template <tpn A>
inline A Min(const A& x, const A& y) { return x < y ? x : y; }
template <tpn A>
inline void Swap(A& x, A& y) { x ^= y ^= x ^= y; }
template <tpn A>
inline A Abs(const A& x) { return x > 0 ? x : -x; }
template <tpn A>
inline A Gcd(register A x, register A y) { return !y ? x : Gcd(y, x % y); }
#endif
#define INF_I32 0x7fffffff
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 5e5 + 5;
const int N = 200;
const int MOD = 998244353;
const db EPS = 1e-6;
char num[N];
int main() {
    const ldb lg2 = log10(2);
    while (~scanf("%s", num) && strcmp("0e0", num)) {
        ldb a = 0.0;
        int b = 0;
        *strchr(num, 'e') = ' ';
        sscanf(num, "%llf%d", &a, &b);
        a = log10(a) + b;
        _fp(m, 0, 9) {
            ldb tmp1 = log10((1 << (m + 1)) - 1);
            _fp(e, 1, 30) {
                ldb tmp2 = tmp1 + lg2 * ((1 << e) - m - 2);
                if (fabs(tmp2 - a) <= EPS) {
                    printf("%d %d", m, e);
                    goto _Fin;
                }
            }
        }
    _Fin:
        puts("");
    }
    return 0;
}