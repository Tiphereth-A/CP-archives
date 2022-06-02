#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
#define __FASTIO__
#define __FUNC__
#ifdef __C_STYLE__
#include <bits/stdc++.h>
#endif
#ifdef __C_LIB__
#include <bits/stdc++.h>
#endif
#ifdef __STL__
#include <bits/stdc++.h>
#endif
#ifdef __DEF__
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
#ifdef __C_LIB__
#endif
#ifdef __CPP_STYLE__
#else
#endif
#endif
#ifdef __FUNC__
#ifndef typename
#endif
template <typename A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <typename A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <typename A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <typename A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
template <typename A>
inline A Gcd(A x, A y) { return !y ? x : Gcd(y, x % y); }
#endif
#ifdef __FASTIO__
#if 1
#ifndef typename
#endif
namespace fastIO {
template <typename A>
inline void read(A &x) {
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
template <typename A, typename B>
inline void read(A &a, B &b) {
    read(a), read(b);
}
template <typename A, typename B, typename C>
inline void read(A &a, B &b, C &c) {
    read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
inline void read(A &a, B &b, C &c, D &d) {
    read(a), read(b), read(c), read(d);
}
}  // namespace fastIO
#endif
#endif
std::map<int, int> set;
inline int qpow(i64 a, i64 b, int mod) {
    int ans = 1;
    for (; b; a = a * a % mod, b >>= 1)
        if (b & 1) ans = ans * a % mod;
    return ans;
}
inline void ex_bsgs(int x, int y, int mod) {
    if (y == 1) {
        puts("0");
        return;
    }
    set.clear();
    int cnt = 0, t = 1;
    for (int d = Gcd(x, mod); d != 1; d = Gcd(x, mod)) {
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
    int m = sqrt(mod) + 1, s = y;
    _rep(i, 0, m) {
        set[s] = i;
        s = 1ll * s * x % mod;
    }
    int tmp = qpow(x, m, mod);
    s = 1ll * t * tmp % mod;
    _for(i, 1, m) {
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