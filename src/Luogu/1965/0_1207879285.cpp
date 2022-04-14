#include <bits/stdc++.h>
#define tpn typename
typedef long long ll;
template <tpn A>
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
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A &a, B &b, C &c, D &d) {
    read(a), read(b), read(c), read(d);
}
ll n, m, k, x;
ll qpower(ll a, ll b) {
    ll r = 1, base = a;
    while (b) {
        if (b & 1) r = r * base % n;
        base = base * base % n;
        b >>= 1;
    }
    return r % n;
}
int main() {
    read(n, m, k, x);
    x = (x % n + m % n * qpower(10, k)) % n;
    printf("%lld", x);
    return 0;
}