#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (auto i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (auto i = (r); i >= (l); --i)
#define _repr(i, r, l) for (auto i = (r); i > (l); --i)
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _err puts("This puzzle has no final configuration.")
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
#define _len(l, r) ((r) - (l) + 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbit_64(x) (1 << __builtin_ctzll(x))
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_inf(a) memset(a, 0x3f, sizeof(a))
#define _debug_cpp(x) std::cerr << #x << " = " << x << std::endl
#define _debug_c(type, x) fprintf(stderr, "#" #x "=%" type "\n", (x))
#define _fin goto FINISHED
typedef long long ll;
typedef unsigned long long ull;
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
const int M = 5e5 + 5, N = 2e5 + 5, MOD = 998244353;
const double EPS = 1e-6;
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    cin >> kase;
    while (kase--) {
        char sudoku[9][9];
        _set_nul(sudoku);
        _for(i, 0, 8)
            _for(j, 0, 8) {
                cin >> sudoku[i][j];
                if (sudoku[i][j] == '9')
                    --sudoku[i][j];
            }
        _for(i, 0, 8) {
            _for(j, 0, 8) { cout << sudoku[i][j]; }
            cout << endl;
        }
    }
FINISHED:
    FastIO::flush();
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
}