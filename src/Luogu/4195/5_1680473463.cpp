#include <cmath>
#include <cstdio>
#include <cstring>
#define rg register
#define rgi register int
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (register int i = (l); i < (r); ++i)
#define tpn typename
#define _err puts("No Solution")
#define _memng(a) memset(a, 0xff, sizeof(a))
typedef long long i64;
template <tpn A>
A Gcd(A x, A y) { return !y ? x : Gcd(y, x % y); }
namespace fastIO {
template <tpn A>
inline void read(A& x) {
    char c;
    A neg = 1;
    do {
        c = getchar();
    } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') neg = -1, c = getchar();
    x = 0;
    do {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    } while (c >= '0' && c <= '9');
    x *= neg;
}
template <tpn A, tpn B>
inline void read(A& a, B& b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A& a, B& b, C& c) {
    read(a), read(b), read(c);
}
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A& a, B& b, C& c, D& d) {
    read(a), read(b), read(c), read(d);
}
} // namespace fastIO
const int N = 2000013;
const int MOD = 2000003;
struct hash {
    int list[N], head[N], next[N], id[N], top;
    il void insert(int val, int y) {
        int k = val % MOD;
        list[++top] = val;
        id[top] = y;
        next[top] = head[k];
        head[k] = top;
    }
    il int find(int val) {
        int k = val % MOD;
        for (rgi i = head[k]; ~i; i = next[i])
            if (list[i] == val) return id[i];
        return -1;
    }
} set;
il int qpow(i64 a, i64 b, int mod) {
    int ans = 1;
    for (; b; a = a * a % mod, b >>= 1)
        if (b & 1) ans = ans * a % mod;
    return ans;
}
il void ex_bsgs(int x, int y, int mod) {
    if (y == 1) {
        puts("0");
        return;
    }
    _memng(set.head);
    rg int cnt = 0, t = 1;
    for (rg int d = Gcd(x, mod); d != 1; d = Gcd(x, mod)) {
        if (y % d) {
            _err;
            return;
        }
        ++cnt;
        y /= d;
        mod /= d;
        t = 1ll * t * x / d % mod;
        if (y == t) {
            printf("%d\n", cnt);
            return;
        }
    }
    rg int m = sqrt(mod) + 1, s = y;
    _rep(i, 0, m) {
        set.insert(s, i);
        s = 1ll * s * x % mod;
    }
    rg int tmp = qpow(x, m, mod);
    s = 1ll * t * tmp % mod;
    _fp(i, 1, m) {
        int tmpp = set.find(s);
        if (~tmpp) {
            printf("%d\n", i * m - tmpp + cnt);
            return;
        }
        s = 1ll * s * tmp % mod;
    }
    _err;
}
int main() {
    int k, x, mod;
    for (;;) {
        fastIO::read(x, mod, k);
        if (k + x + mod)
            ex_bsgs(x % mod, k % mod, mod);
        else
            return 0;
    }
    return 0;
}