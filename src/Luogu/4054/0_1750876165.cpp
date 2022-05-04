#include <bits/stdc++.h>
#define tpn typename
#define _lowbit(x) (1 << __builtin_ctz(x))
typedef double db;
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
inline A Gcd(A x, A y) {
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
const int M = 1e2 + 5;
const int N = 3e2 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int n, m, tr[M][N][N], a[N][N];
void modify(int color, int x, int y, int k) {
    for (int i = x; i <= n; i += _lowbit(i))
        for (int j = y; j <= m; j += _lowbit(j))
            tr[color][i][j] += k;
}
int query(int color, int x, int y) {
    int ans = 0;
    for (int i = x; i; i -= _lowbit(i))
        for (int j = y; j; j -= _lowbit(j))
            ans += tr[color][i][j];
    return ans;
}
int main(int argc, char const *argv[]) {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    read(n, m);
    for (int i = 1, tmp; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            read(tmp);
            modify(a[i][j] = tmp, i, j, 1);
        }
    int q;
    read(q);
    for (int i = 1, o, x1, x2, y1, y2, c; i <= q; ++i) {
        read(o);
        if (o & 1) {
            read(x1, y1, c);
            modify(a[x1][y1], x1, y1, -1);
            modify(a[x1][y1] = c, x1, y1, 1);
        } else {
            read(x1, x2, y1, y2, c);
            print(query(c, x2, y2) - query(c, x2, y1 - 1) - query(c, x1 - 1, y2) +
                  query(c, x1 - 1, y1 - 1));
        }
    }
ex:
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
