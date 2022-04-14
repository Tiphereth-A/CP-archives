#define __DEF__
#include <bits/stdc++.h>
#ifdef __DEF__
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
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) (((l) + (r)) >> 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbitll(x) (1 << __builtin_ctzll(x))
#define _mem(a) memset(a, 0, sizeof(a))
#define _meminf(a) memset(a, 0x3f, sizeof(a))
#define _debug_cpp(x) std::cout << #x << " = " << x << std::endl
#define _debug_c(type, x) printf("#" #x "=%" type "\n", (x))
typedef long long ll;
typedef unsigned long long ull;
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
void read() {}
void print() {}
template <typename T, typename... T2>
inline void read(T &x, T2 &...oth) {
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
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
const int M = 5e5 + 5;
const int N = 1e6 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int root[N << 5];
int n, m, a[N];
struct Persistable_Segment_Tree {
    int cnt_node;
    struct node {
        int n, l, r;
    } tr[N << 5];
#define PRE tr[pre]
#define NOW tr[now]
    void init(int l, int r, int &now) {
        now = ++cnt_node;
        if (l == r) {
            tr[now].n = a[l];
            return;
        }
        int mid = l + ((r - l) >> 1);
        init(l, mid, NOW.l);
        init(mid + 1, r, NOW.r);
    }
    void modify(int l, int r, int &now, int pre, int pos, int k) {
        tr[now = ++cnt_node] = PRE;
        if (l == r) {
            NOW.n = k;
            return;
        }
        int mid = l + ((r - l) >> 1);
        if (pos <= mid)
            modify(l, mid, NOW.l, PRE.l, pos, k);
        else
            modify(mid + 1, r, NOW.r, PRE.r, pos, k);
    }
    int query(int now, int l, int r, int pos) {
        if (l == r) return NOW.n;
        int mid = l + ((r - l) >> 1);
        if (pos <= mid)
            return query(NOW.l, l, mid, pos);
        else
            return query(NOW.r, mid + 1, r, pos);
    }
} T;
int main(int argc, char const *argv[]) {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    read(n, m);
    _for(i, 1, n) read(a[i]);
    T.init(1, n, root[0]);
    int v, op, loc, value;
    _for(i, 1, m) {
        read(v, op, loc);
        if (op & 1) {
            read(value);
            T.modify(1, n, root[i], root[v], loc, value);
        } else
            print(T.query(root[i] = root[v], 1, n, loc));
    }
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
