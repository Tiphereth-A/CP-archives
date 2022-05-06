#define __DEF__
#include <bits/stdc++.h>
#ifdef __DEF__
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double db;
template <typename A>
inline A Max(const A &x, const A &y) { return x > y ? x : y; }
template <typename A>
inline A Min(const A &x, const A &y) { return x < y ? x : y; }
template <typename A>
inline void Swap(A &x, A &y) { x ^= y ^= x ^= y; }
template <typename A>
inline A Abs(const A &x) { return x > 0 ? x : -x; }
template <typename A>
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
const int M = 1e5 + 5;
const int N = 2e4 + 5;
const int MOD = 998244353;
const db EPS = 1e-6;
int n, m;
struct node {
    int a, b, c;
    bool operator<(const node &a) const { return c > a.c; }
} e[M];
int fa[N], enemy[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main(int argc, char const *argv[]) {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    read(n, m);
    _for(i, 1, m) read(e[i].a, e[i].b, e[i].c);
    _for(i, 1, n) fa[i] = i;
    std::sort(e + 1, e + m + 1);
    _for(i, 1, m + 1) {
        int x = e[i].a, y = e[i].b;
        if (find(x) == find(y)) {
            std::cout << e[i].c;
            return 0;
        }
        if (!enemy[fa[x]])
            enemy[fa[x]] = fa[y];
        else
            merge(enemy[fa[x]], fa[y]);
        x ^= y ^= x ^= y;
        if (!enemy[fa[x]])
            enemy[fa[x]] = fa[y];
        else
            merge(enemy[fa[x]], fa[y]);
    }
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
