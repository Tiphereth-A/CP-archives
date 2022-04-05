#include <cstdio>
#define tpn typename
typedef long long ll;
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Gcd(const A &x, const A &y) {
    return y ? Gcd(y, x % y) : x;
}
template <tpn A>
inline void ExGcd(const A &a, const A &b, A &x, A &y) {
    if (!b) return (void)(x = 1, y = 0);
    ExGcd(b, a % b, y, x);
    y -= a / b * x;
}
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
template <tpn A, tpn B, tpn C, tpn D, tpn E>
inline void read(A &a, B &b, C &c, D &d, E &e) {
    read(a), read(b), read(c), read(d), read(e);
}
ll X, Y, M, N, L;
int main() {
    read(X, Y, M, N, L);
    if (M - N < 0) Swap(M, N), Swap(X, Y);
    ll a = M - N, b = L, c = Y - X, g = Gcd(a, b), m = L / g, x = 0, y = 0;
    ExGcd(a, b, x, y);
    if (c % g)
        printf("Impossible\n");
    else
        printf("%lld\n", ((x * (c / g)) % m + m) % m);
    return 0;
}