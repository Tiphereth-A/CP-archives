#define __DEF__
#include <bits/stdc++.h>
#ifdef __DEF__
#define tpn typename
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
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
const int M = 5e5 + 5;
const int N = 1e5 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int n, w, a[N], final[N];
int tr[N << 2];
void build(int p, int l, int r) {
    if (l == r) {
        tr[p] = final[l];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(_lch, l, mid);
    build(_rch, mid + 1, r);
    tr[p] = Max(tr[_lch], tr[_rch]);
}
int main(int argc, char const *argv[]) {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    read(n, w);
    if (w == 0) {
        print(0);
        goto end;
    }
    int x, b;
    _for(i, 1, n) {
        read(x, b);
        a[x] += b;
    }
    _for(i, 1, w) final[0] += a[i];
    _for(i, 1, n - w) final[i] = final[i - 1] + a[i + w] - a[i];
    build(1, 1, n - w);
    print(tr[1]);
end:
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
