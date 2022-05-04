#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define tpn typename
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
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
template <tpn A, tpn B>
inline void read(A &a, B &b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A &a, B &b, C &c) {
    read(a), read(b), read(c);
}
template <tpn A, tpn B, tpn C, tpn D>
inline void read(A &a, B &b, C &c, D &d) {
    read(a), read(b), read(c), read(d);
}
template <tpn A>
inline void write(A &x) {
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}
const int M = 200005;
const int N = 20000;
const int INF = 0x7fffffff;
struct bign {
    int n[50000];
    bign() { memset(n, 0, sizeof(n)); }
    void print() {
        _rfor(i, n[0], 1) putchar(n[i] + '0');
        puts("");
    }
    bign operator=(const bign a) {
        memset(n, 0, sizeof(n));
        _for(i, 0, a.n[0]) n[i] = a.n[i];
        return *this;
    }
    bign operator*(const bign a) const {
        bign c;
        int i;
        for (i = 1; i <= a.n[0]; i++)
            _for(j, 1, n[0]) c.n[i + j - 1] += a.n[i] * n[j];
        for (i = 1; i <= a.n[0] + n[0] - 1; i++) {
            c.n[i + 1] += c.n[i] / 10;
            c.n[i] %= 10;
        }
        for (; c.n[i] == 0; i--)
            ;
        c.n[0] = i;
        return c;
    }
};
int main() {
    int n;
    scanf("%d", &n);
    struct bign a, tmp;
    a.n[0] = a.n[1] = tmp.n[0] = 1;
    tmp.n[1] = 2;
    for (; n; n >>= 1, tmp = tmp * tmp)
        if (n & 1) a = a * tmp;
    a.n[1]--;
    a.print();
    return 0;
}