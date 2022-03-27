#include <cctype>
#include <cstdio>
#define _lowbit(x) (1 << __builtin_ctz(x))
typedef long long i64;
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
inline int getc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
void read() {}
void print() {}
template <typename T, typename... T2>
inline void read(T& x, T2&... oth) {
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
} // namespace FastIO
using FastIO::print;
using FastIO::read;
const int N = 5e5 + 5;
i64 a[N];
int m, n;
void add(int pos, i64 x) {
    for (; pos <= n; pos += _lowbit(pos))
        a[pos] += x;
}
i64 query(int pos) {
    i64 ans = 0;
    for (; pos; pos -= _lowbit(pos))
        ans += a[pos];
    return ans;
}
i64 b[N];
int main(int argc, char const* argv[]) {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    for (int i = 1; i <= n; ++i)
        add(i, b[i] - b[i - 1]);
    i64 k;
    for (int i = 1, x, y, o; i <= m; ++i) {
        read(o, x);
        if (o & 1) {
            read(y, k);
            add(x, k);
            add(y + 1, -k);
        } else
            print(query(x));
    }
ex:
    FastIO::flush();
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
