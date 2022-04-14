#include <bits/stdc++.h>
using namespace std;
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
    x = 0;
    char ch = getc();
    while (!isdigit(ch)) {
        ch = getc();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getc();
    }
    read(oth...);
}
inline void flush() {
    fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
}
template <typename T, typename... T2>
inline void print(T x, T2... oth) {
    if (p3 > 1 << 20)
        flush();
    do {
        a[++p] = x % 10 + 48;
    } while (x /= 10);
    do {
        buf2[++p3] = a[p];
    } while (--p);
    buf2[++p3] = hh;
    print(oth...);
}
inline void putchar(char a) {
    buf2[++p3] = a;
    if (p3 > 1 << 20)
        flush();
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    __uint128_t k, x;
    read(k, x);
    if (k <= 20) {
        __uint128_t ans = 1;
        for (int i = 1; i <= k; ++i) ans *= 10;
        print(ans + x);
    } else {
        __uint128_t _ = x;
        while (_) {
            --k;
            _ /= 10;
        }
        putchar('1');
        while (k--) putchar('0');
        if (x) print(x);
    }
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}