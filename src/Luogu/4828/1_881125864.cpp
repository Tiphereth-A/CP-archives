#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define tpn typename
typedef unsigned int u32;
typedef unsigned long long ull;
typedef long long ll;
typedef __int128 i128;
typedef double db;
typedef long double ldb;
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
A Gcd(const A &x, const A &y) {
    return y ? Gcd(y, x % y) : x;
}
template <tpn A>
inline void read(A &x) {
    char c;
    do { c = getchar(); } while ((c < '0' || c > '9'));
    x = 0;
    do {
        x = (x << 3) + (x << 1) + (c - 48);
        c = getchar();
    } while (c >= '0' && c <= '9');
}
template <tpn A, tpn B>
inline void read(A &a, B &b) { read(a), read(b); }
template <tpn A, tpn B, tpn C>
inline void read(A &a, B &b, C &c) { read(a), read(b), read(c); }
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A &a, B &b, C &c, D &d) { read(a), read(b), read(c), read(d); }
int Max(int a, int b) { return a > b ? a : b; }
int Min(int a, int b) { return a < b ? a : b; }
int Abs(int a) { return a > 0 ? a : -a; }
#define N 1000005
#define M 2005
const int MOD = 998244353;
int a[N];
int n, q, x, y;
i64 c[M][M] = {1};
int main() {
    read(n);
    _for(i, 1, n) read(a[i]);
    _for(i, 1, 2000) {
        c[i][0] = c[i][i] = 1;
        _for(j, 1, i - 1) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
    read(q);
    while (q--) {
        i64 ans = 0;
        read(x, y);
        for (int i = 0; i <= x; ++i) {
            ans = (ans + a[y] * c[x][i]) % MOD;
            ((++y) > n) ? (y = 1) : 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
