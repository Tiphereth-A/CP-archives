#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
using db = double;
using ldb = long double;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
#define _for_graph(head, e, i, now) for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_inf(a) memset(a, 0x3f, sizeof(a))
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
#define _set_inf_n(a, n) memset(a, 0x3f, sizeof(a[0]) * (n))
#define _fin goto FINISHED
#define _divb(l, r, n, expressions)                   \
    for (decltype(n) l = 2, r; l <= (n); l = r + 1) { \
        r = (n) / ((n) / l);                          \
        expressions;                                  \
    }
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
#define _run_fin(expressions) \
    {                         \
        expressions;          \
        _fin;                 \
    }
#define _run_break(expressions) \
    {                           \
        expressions;            \
        break;                  \
    }
#define _run_continue(expressions) \
    {                              \
        expressions;               \
        continue;                  \
    }
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
#define _len(l, r) ((r) - (l) + 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbit_64(x) (1 << __builtin_ctzll(x))
#define _debug                                              \
    {                                                       \
        fprintf(stderr, "%d %s\n", __LINE__, __FUNCTION__); \
        fflush(stderr);                                     \
    }
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const int OFFSET = 5;
const int N = 5e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf;
int p, p3 = -1;
inline int getc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++; }
inline void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
inline void read() {}
template <class T>
inline void read(T &x) {
    int f = x = 0;
    char ch = getc();
    while (!isdigit(ch)) {
        if (ch == '-') f = 1;
        ch = getc();
    }
    while (isdigit(ch)) { x = x * 10 + ch - '0', ch = getc(); }
    if (f) x = -x;
}
template <typename T, typename... T2>
inline void read(T &x, T2 &...oth) {
    read(x);
    read(oth...);
}
inline void print() {}
inline void print(char a) { buf2[++p3] = a; }
template <class T>
inline void print(T x) {
    do { a[++p] = x % 10 + 48; } while (x /= 10);
    do { buf2[++p3] = a[p]; } while (--p);
}
template <typename T, typename... T2>
inline void print(T x, T2... oth) {
    if (p3 > 1 << 20) flush();
    print(x);
    print(oth...);
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
#define MULTI_CASES
void solve() {
    i64 n, p;
    read(n, p);
    if (p == 1) {
        puts("0");
        return;
    }
    if (p > n) {
        printf("%lld\n", n);
        return;
    }
    i64 ans = n, _n = n;
    i128 _p = p;
    int f = -1;
    while (_n / _p) {
        ans += f * (_n / _p);
        _p *= p;
        f *= -1;
    }
    printf("%lld\n", ans);
}
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
#ifdef MULTI_CASES
    int _t;
    read(_t);
    while (_t--)
#endif
        solve();
FINISHED:
    FastIO::flush();
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}