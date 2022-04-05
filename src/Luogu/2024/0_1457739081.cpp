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
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
#define _line(l, r) ((r) - (l) + 1)
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
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
inline int getc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++; }
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
inline void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
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
template <typename T>
inline void print_h(T x, char h) {
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
    buf2[++p3] = h;
}
inline void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
#define print_h FastIO::print_h
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 5e5 + 5;
const int N = 5e4 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int n, k, ans;
int fa[N * 3];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool j1(int x, int y) {
    return find(x) == find(y + n) ||
           find(x + n) == find(y);
}
bool j2(int x, int y) {
    return find(x) == find(y) ||
           find(x) == find(y + n);
}
void merge_enemy(int x, int y) {
    fa[find(x)] = find(y + n * 2);
    fa[find(x + n)] = find(y);
    fa[find(x + n * 2)] = find(y + n);
}
void merge_alay(int x, int y) {
    fa[find(x)] = find(y);
    fa[find(x + n)] = find(y + n);
    fa[find(x + n * 2)] = find(y + n * 2);
}
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    freopen("D:\\code\\IO\\err.err", "w", stderr);
    clock_t c1 = clock();
#endif
    read(n, k);
    _fp(i, 1, n * 3) fa[i] = i;
    for (int op, x, y, i = 1; i <= k; ++i) {
        read(op, x, y);
        if (x > n || y > n) {
            ++ans;
            continue;
        }
        if (op == 2 && x == y) {
            ++ans;
            continue;
        }
        if (op == 1) {
            if (j1(x, y)) {
                ++ans;
                continue;
            }
            merge_alay(x, y);
        } else {
            if (j2(x, y)) {
                ++ans;
                continue;
            }
            merge_enemy(x, y);
        }
    }
    std::cout << ans;
    FastIO::flush();
#ifndef ONLINE_JUDGE
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
