#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define rg register
#define rgi register int
#define il inline
#define tpn typename
#define sstream std::stringstream
#define SYNC std::ios::sync_with_stdio(false)
#define UNTIE std::cin::tie(0), std::cout::tie(0)
#define _for(i, l, r) for (register int i = (l); i <= (r); ++i)
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
#define fin goto ex
typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
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
    x ^= y ^= x ^= y;
}
template <tpn A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
template <tpn A>
inline A Gcd(register A x, register A y) {
    return !y ? x : Gcd(y, x % y);
}
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
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
inline void putchar(char a) {
    buf2[++p3] = a;
}
}  // namespace FastIO
using FastIO::print;
using FastIO::print_h;
using FastIO::read;
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 5e5 + 5;
const int N = 2e6 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int n, m, c;
i64 a[N], tr[N];
struct node {
    int l, r, id;
    i64 ans;
} q[N];
void add(int pos, int k) {
    for (; pos <= n; pos += _lowbit(pos))
        tr[pos] += k;
}
i64 query(int pos) {
    i64 ans = 0;
    for (; pos; pos -= _lowbit(pos))
        ans += tr[pos];
    return ans;
}
int next[N], pos[N];
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    read(n, c, m);
    _for(i, 1, n) read(a[i]);
    _fd(i, n, 1) {
        next[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    _for(i, 1, c) {
        if (pos[i] && next[pos[i]])
            add(next[pos[i]], 1);
    }
    _for(i, 1, m) {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    std::sort(q + 1, q + m + 1, [](const node &a, const node &b) {
        return (a.l == b.l) ? a.r < b.r : a.l < b.l;
    });
    int l = 1;
    _for(i, 1, m) {
        for (; l < q[i].l; ++l)
            if (next[l]) {
                add(next[l], -1);
                if (next[next[l]])
                    add(next[next[l]], 1);
            }
        q[i].ans = query(q[i].r) - query(q[i].l - 1);
    }
    std::sort(q + 1, q + m + 1, [](const node &a, const node &b) { return a.id < b.id; });
    _for(i, 1, m) print(q[i].ans);
ex:
    FastIO::flush();
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
