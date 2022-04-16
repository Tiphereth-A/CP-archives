#include <bits/stdc++.h>
#define sstream std::stringstream
#define SYNC std::ios::sync_with_stdio(false)
#define UNTIE std::cin::tie(0), std::cout::tie(0)
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (auto i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (auto i = (r); i >= (l); --i)
#define _repr(i, r, l) for (auto i = (r); i > (l); --i)
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
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
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
const int M = 1 << 16;
const int N = 17;
const int MOD = 998244353;
const db EPS = 1e-6;
i64 f[M][N], s[N], n, delta;
int main(int argc, char const *argv[]) {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    read(n, delta);
    _rep(i, 0, n) read(s[i]);
    _rep(i, 0, n) f[1 << i][i] = 1;
    _rep(i, 0, 1 << n) {
        _rep(j, 0, n) {
            if (!(i & (1 << j)))
                continue;
            _rep(k, 0, n) {
                if (i & (1 << k))
                    continue;
                if (s[j] - s[k] > delta || s[k] - s[j] > delta)
                    f[i | (1 << k)][k] += f[i][j];
            }
        }
    }
    i64 ans = 0;
    _rep(i, 0, n) ans += f[(1 << n) - 1][i];
    print(ans);
ex:
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
