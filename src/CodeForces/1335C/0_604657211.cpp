#include <bits/stdc++.h>
using namespace std;

#define SYNC std::ios::sync_with_stdio(false)
#define UNTIE std::cin.tie(0), std::cout.tie(0)
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (auto i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (auto i = (r); i >= (l); --i)
#define _repr(i, r, l) for (auto i = (r); i > (l); --i)
#define _gc getchar
#define _pc putchar
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _debug_cpp(x) std::cerr << #x << " = " << x << std::endl
#define _debug_c(type, x) fprintf(stderr, "#" #x "=%" type "\n", (x))
#define _fin goto FINISHED
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
const int M = 5e5 + 5, N = 2e5 + 5, MOD = 998244353;
int cnt[N];
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    read(kase);
    while (kase--) {
        int n;
        read(n);
        _set_nul(cnt);
        int cnt_max = 0, cnt_num = 0;
        _for(i, 1, n) {
            int tmp;
            read(tmp);
            if (!cnt[tmp])
                ++cnt_num;
            ++cnt[tmp];
            if (cnt[tmp] > cnt_max)
                cnt_max = cnt[tmp];
        }
        print(cnt_max < cnt_num ? cnt_max : cnt_num - (cnt_max == cnt_num));
    }
FINISHED:
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
}