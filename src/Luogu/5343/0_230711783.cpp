#define __DEF__
#include <bits/stdc++.h>
#ifdef __DEF__
#define rg register
#define rgi register int
#define il inline
#define tpn typename
#define sstream std::stringstream
#define SYNC std::ios::sync_with_stdio(false)
#define UNTIE std::cin::tie(0), std::cout::tie(0)
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (register int i = (l); i < (r); ++i)
#define _replu(i, l, r) for (register long unsigned int i = (l); i < (r); ++i)
#define _fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define _repr(i, r, l) for (register int i = (r); i > (l); --i)
#define _gc getchar
#define _pc putchar
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _err puts("This puzzle has no final configuration.")
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define _mid(l, r) (((l) + (r)) >> 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbitll(x) (1 << __builtin_ctzll(x))
#define _mem(a) memset(a, 0, sizeof(a))
#define _meminf(a) memset(a, 0x3f, sizeof(a))
#define _debug_cpp(x) std::cout << #x << " = " << x << std::endl
#define _debug_c(type, x) printf("#" #x "=%" type "\n", (x))
typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
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
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
inline int getc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++; }
void read() {}
void print() {}
template <typename T, typename... T2>
inline void read(T& x, T2&... oth) {
    int f = 0;
    x = 0;
    char ch = getc();
    while (!isdigit(ch)) {
        if (ch == '-') f = 1;
        ch = getc();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getc();
    }
    if (f) x = -x;
    read(oth...);
}
inline void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T, typename... T2>
inline void print(T x, T2... oth) {
    if (p3 > 1 << 20) flush();
    if (x < 0) buf2[++p3] = 45, x = -x;
    do { a[++p] = x % 10 + 48; } while (x /= 10);
    do { buf2[++p3] = a[p]; } while (--p);
    buf2[++p3] = hh;
    print(oth...);
}
} // namespace FastIO
#define read FastIO::read
#define print FastIO::print
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 5e5 + 5;
const int N = 1e2 + 1;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
i64 n;
std::bitset<N> b1, b2;
int cnt, arr[N];
struct mat {
    int num[N][N];
    inline void operator*=(const mat& a) {
        int c[N][N];
        _mem(c);
        _rep(i, 1, N) _rep(j, 1, N) {
            int& tmp = c[i][j];
            _rep(k, 1, N)
                tmp = ((i64)num[i][k] * a.num[k][j] + tmp) % MOD;
        }
        memcpy(num, c, sizeof(num));
    }
} a;
struct col_vector {
    int num[N];
    inline void operator*=(const mat& a) {
        int c[N];
        _mem(c);
        _rep(i, 1, N) {
            int& tmp1 = c[i];
            const int* tmp2 = a.num[i];
            _rep(j, 1, N) tmp1 = ((i64)num[j] * tmp2[j] + tmp1) % MOD;
        }
        memcpy(num, c, sizeof(num));
    }
} dp;
inline void pow(mat a, i64 b, col_vector& ret) {
    for (; b; b >>= 1, a *= a)
        if (b & 1) ret *= a;
}
int main(int argc, char const* argv[]) {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    int k, p;
    read(n);
    read(k);
    while (k--) {
        read(p);
        b1[p] = 1;
    }
    read(k);
    while (k--) {
        read(p);
        b2[p] = 1;
    }
    b1 &= b2;
    int* tmp = a.num[100];
    _rep(i, 1, N) {
        if (b1[i]) {
            tmp[101 - i] = dp.num[i] = 1;
            arr[++cnt] = i;
        }
    }
    _rep(i, 1, 100) a.num[i][i + 1] = 1;
    _fp(i, 1, Min(100ll, n)) {
        _fp(j, 1, cnt) {
            if (i - arr[j] > 0)
                dp.num[i] = ((i64)dp.num[i] + dp.num[i - arr[j]]) % MOD;
            else
                break;
        }
    }
    if (n <= 100)
        print(dp.num[n]);
    else {
        pow(a, n - 100, dp);
        print(dp.num[100]);
    }
    FastIO::flush();
#ifndef ONLINE_JUDGE
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
