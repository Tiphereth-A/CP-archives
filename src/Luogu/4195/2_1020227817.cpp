#include <cmath>
#include <cstdio>
#include <map>
#define rg register
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (register int i = (l); i < (r); ++i)
#define tpn typename
#define _err puts("No Solution")
template <tpn A>
inline A Gcd(register A x, register A y) { return !y ? x : Gcd(y, x % y); }
typedef long long i64;
std::map<int, int> set;
il int qpow(rg i64 a, rg i64 b, rg int mod) {
    rg int ans = 1;
    for (; b; a = a * a % mod, b >>= 1)
        if (b & 1) ans = ans * a % mod;
    return ans;
}
il void ex_bsgs(rg int x, rg int y, rg int mod) {
    if (y == 1) {
        puts("0");
        return;
    }
    set.clear();
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
        set[s] = i;
        s = 1ll * s * x % mod;
    }
    rg int tmp = qpow(x, m, mod);
    s = 1ll * t * tmp % mod;
    _fp(i, 1, m) {
        if (set.count(s)) {
            printf("%d\n", i * m - set[s] + cnt);
            return;
        }
        s = 1ll * s * tmp % mod;
    }
    _err;
}
int main() {
    int k, x, mod;
    for (scanf("%d%d%d", &x, &mod, &k); k + x + mod;) {
        ex_bsgs(x % mod, k % mod, mod);
        scanf("%d%d%d", &x, &mod, &k);
    }
    return 0;
}