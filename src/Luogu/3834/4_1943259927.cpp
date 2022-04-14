#define __C_EX__
#define __CPP_EX__
#define __DEF__
#define __O_MAGIC__
#include <bits/stdc++.h>
#ifdef __C_EX__
#include <bits/stdc++.h>
#endif
#ifdef __CPP_EX__
#include <bits/stdc++.h>
#endif
#ifdef __O_MAGIC__
#endif
#ifdef __DEF__

#define rgi int

#define tpn typename
#define sstream std::stringstream
#define SYNC std::ios::sync_with_stdio(false)
#define UNTIE std::cin::tie(0), std::cout::tie(0)
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
#define _replu(i, l, r) for (long unsigned int i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define _repr(i, r, l) for (int i = (r); i > (l); --i)
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
inline A Max(const A &x, const A &y) { return x > y ? x : y; }
template <tpn A>
inline A Min(const A &x, const A &y) { return x < y ? x : y; }
template <tpn A>
inline void Swap(A &x, A &y) { x ^= y ^= x ^= y; }
template <tpn A>
inline A Abs(const A &x) { return x > 0 ? x : -x; }
template <tpn A>
inline A Gcd(A x, A y) { return !y ? x : Gcd(y, x % y); }
#endif
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
inline int getc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++; }
template <tpn Type>
inline void read_digit(Type &x) {
    int ret = 0, f = 0;
    char ch = getc();
    while (!isdigit(ch)) {
        if (ch == '-') f = 1;
        ch = getc();
    }
    while (isdigit(ch)) {
        ret = ret * 10 + ch - 48;
        ch = getc();
    }
    x = f ? -ret : ret;
}
template <tpn A, tpn B>
inline void read_digit(A &a, B &b) { read_digit(a), read_digit(b); }
template <tpn A, tpn B, tpn C>
inline void read_digit(A &a, B &b, C &c) { read_digit(a), read_digit(b), read_digit(c); }
template <tpn A, tpn B, tpn C, tpn D>
inline void read_digit(A &a, B &b, C &c, D &d) { read_digit(a), read_digit(b), read_digit(c), read_digit(d); }
inline void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <tpn Type>
inline void print_digit(Type x) {
    if (p3 > 1 << 20) flush();
    if (x < 0) buf2[++p3] = 45, x = -x;
    do { a[++p] = x % 10 + 48; } while (x /= 10);
    do { buf2[++p3] = a[p]; } while (--p);
    buf2[++p3] = hh;
}
}  // namespace FastIO
#define read FastIO::read_digit
#define print FastIO::print_digit
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 5e5 + 5;
const int N = 2e5 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int n, m;
int a[N], b[N], b_len;
struct chman_tree {
    int val, l, r;
} tree[N << 5];
int root[N << 5], node_cnt;
#define PRE tree[pre]
#define PREL tree[L]
#define PRER tree[R]
#define NOW tree[now]
void modify(int pre, int l, int r, int &now, int pos) {
    tree[now = ++node_cnt] = {PRE.val + 1, PRE.l, PRE.r};
    if (l == r) return;
    int mid = _mid(l, r);
    if (pos <= mid)
        modify(PRE.l, l, mid, NOW.l, pos);
    else
        modify(PRE.r, mid + 1, r, NOW.r, pos);
}
int query(int L, int R, int l, int r, int k) {
    if (l == r) return l;
    int mid = _mid(l, r), tmp = tree[PRER.l].val - tree[PREL.l].val;
    if (k <= tmp)
        return query(PREL.l, PRER.l, l, mid, k);
    else
        return query(PREL.r, PRER.r, mid + 1, r, k - tmp);
}
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
#endif
    clock_t c1 = clock();
    read(n, m);
    _for(i, 1, n) {
        read(a[i]);
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    b_len = std::unique(b + 1, b + n + 1) - b - 1;
    _for(i, 1, n) modify(root[i - 1], 1, b_len, root[i], std::lower_bound(b + 1, b + b_len + 1, a[i]) - b);
    int l, r, k;
    while (m--) {
        read(l, r, k);
        print(b[query(root[l - 1], root[r], 1, b_len, k)]);
    }
    FastIO::flush();
    std::cerr << "Time:" << clock() - c1 << std::endl;
    return 0;
}
