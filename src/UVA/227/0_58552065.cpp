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
inline A Max(const A &x, const A &y) { return x > y ? x : y; }
template <tpn A>
inline A Min(const A &x, const A &y) { return x < y ? x : y; }
template <tpn A>
inline void Swap(A &x, A &y) { x ^= y ^= x ^= y; }
template <tpn A>
inline A Abs(const A &x) { return x > 0 ? x : -x; }
template <tpn A>
inline A Gcd(register A x, register A y) { return !y ? x : Gcd(y, x % y); }
#endif
#define INF_I32 0x7fffffff
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 500005;
const int N = 1e3 + 5;
const int MOD = 998244353;
char map[7][7];
il bool legel(int i, int j) { return i > 0 && i < 6 && j > 0 && j < 6; }
il void output() {
    _fp(i, 1, 5) {
        _fp(j, 1, 4) printf("%c ", map[i][j]);
        printf("%c\n", map[i][5]);
    }
}
int main() {
    char c;
    int kase = 0;
    int nowi = -1, nowj = -1;
    while (!feof(stdin)) {
        int nowi = -1, nowj = -1;
        _mem(map);
        _fp(i, 1, 5) {
            _fp(j, 1, 5) {
                map[i][j] = (c = _gc());
                if (c == ' ') {
                    nowi = i;
                    nowj = j;
                }
                if (c == 'Z') return 0;
            }
            while (_gc() != '\n')
                ;
        }
        if (kase) puts("");
        printf("Puzzle #%d:\n", ++kase);
        int flag = 0;
        while (c != '0' && ~(c = _gc())) {
            switch (c) {
                case '\r':
                case '\n':
                    break;
                case 'A':
                    if (flag) break;
                    if (legel(nowi - 1, nowj)) {
                        Swap(map[nowi - 1][nowj], map[nowi][nowj]);
                        nowi--;
                    } else {
                        _err;
                        flag = 1;
                    }
                    break;
                case 'B':
                    if (flag) break;
                    if (legel(nowi + 1, nowj)) {
                        Swap(map[nowi + 1][nowj], map[nowi][nowj]);
                        nowi++;
                    } else {
                        _err;
                        flag = 1;
                    }
                    break;
                case 'L':
                    if (flag) break;
                    if (legel(nowi, nowj - 1)) {
                        Swap(map[nowi][nowj - 1], map[nowi][nowj]);
                        nowj--;
                    } else {
                        _err;
                        flag = 1;
                    }
                    break;
                case 'R':
                    if (flag) break;
                    if (legel(nowi, nowj + 1)) {
                        Swap(map[nowi][nowj + 1], map[nowi][nowj]);
                        nowj++;
                    } else {
                        _err;
                        flag = 1;
                    }
                    break;
                case '0':
                    if (flag) break;
                    output();
                    break;
                default:
                    if (flag) break;
                    _err;
                    flag = 1;
            }
        }
        while (_gc() != '\n')
            ;
    }
    return 0;
}