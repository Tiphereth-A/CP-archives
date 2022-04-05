#include <bits/stdc++.h>
#define i32_r register int
#define il __inline__ __attribute__((always_inline))
#define SYNC std::ios::sync_with_stdio(false)
#define UNTIE std::cin::tie(0), std::cout::tie(0)
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (auto i = (l); i < (r); ++i)
#define _fd(i, r, l) for (auto i = (r); i >= (l); --i)
#define _repr(i, r, l) for (auto i = (r); i > (l); --i)
#define _gc getchar
#define _pc putchar
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _err puts("This puzzle has no final configuration.")
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
#define _len(l, r) ((r) - (l) + 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbit_64(x) (1 << __builtin_ctzll(x))
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_inf(a) memset(a, 0x3f, sizeof(a))
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
#define _set_inf_n(a, n) memset(a, 0x3f, sizeof(a[0]) * (n))
#define _debug_cpp(x) std::cerr << #x << " = " << x << std::endl
#define _debug_c(type, x) fprintf(stderr, "#" #x "=%" type "\n", (x))
#define _fin goto FINISHED
typedef long long i64;
typedef unsigned long long u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef double db;
typedef long double ldb;
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = ' ';
int p, p3 = -1;
inline int getc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
void read() {}
void print() {}
template <typename T, typename... T2>
inline void read(T &x, T2 &...oth) {
    int f = 0;
    x = 0;
    char ch = getc();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = 1;
        ch = getc();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getc();
    }
    if (f)
        x = -x;
    read(oth...);
}
inline void flush() {
    fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
}
template <typename T, typename... T2>
inline void print(T x, T2... oth) {
    if (p3 > 1 << 20)
        flush();
    if (x < 0)
        buf2[++p3] = 45, x = -x;
    do {
        a[++p] = x % 10 + 48;
    } while (x /= 10);
    do {
        buf2[++p3] = a[p];
    } while (--p);
    buf2[++p3] = hh;
    print(oth...);
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int M = 5e5 + 5, N = 1e6 + 5, MOD = 998244353;
const db EPS = 1e-6;
int a[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t c1 = clock();
#endif
    int n, m;
    read(n, m);
    int _;
    _for(i, 1, n) read(a[i]);
    _for(i, 1, m) {
        read(_);
        int __ = std::lower_bound(a + 1, a + n + 1, _) - a;
        print(a[__] == _ ? __ : -1);
    }
FINISHED:
    FastIO::flush();
#ifndef ONLINE_JUDGE
    std::cerr << "\n--------\n"
              << "Time used:" << clock() - c1 << std::endl;
#endif
    return 0;
}
