#include <cctype>
#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define tpn typename
typedef long long i64;
#define MAXBUF 1 << 14
inline char gc() {
    static char buf[MAXBUF], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin), p1 == p2) ? EOF : *p1++;
}
template <tpn A>
inline void read(A& x) {
    char c;
    do {
        c = gc();
    } while (!isdigit(c));
    x = 0;
    do {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    } while (isdigit(c));
}
template <tpn A, tpn B>
inline void read(A& a, B& b) {
    read(a), read(b);
}
template <tpn A, tpn B, tpn C>
inline void read(A& a, B& b, C& c) {
    read(a), read(b), read(c);
}
int Max(int x, int y) {
    int m = (x - y) >> 31;
    return y & m | x & ~m;
}
int Min(int x, int y) {
    int m = (x - y) >> 31;
    return y & ~m | x & m;
}
i64 Abs(i64 x) {
    i64 y = x >> 63;
    return (x + y) ^ y;
}
#define N 200005
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
int n, m, w[N], v[N], l[N], r[N];
i64 s, prew[N], prev[N], sum, y;
bool inline check(int num) {
    y = 0;
    fp(i, 1, n) if (w[i] >= num) {
        prew[i] = prew[i - 1] + 1;
        prev[i] = prev[i - 1] + v[i];
    }
    else {
        prew[i] = prew[i - 1];
        prev[i] = prev[i - 1];
    }
    int tmpl, tmpr;
    fp(i, 1, m) {
        tmpl = l[i] - 1;
        tmpr = r[i];
        y += (prew[tmpr] - prew[tmpl]) * (prev[tmpr] - prev[tmpl]);
    }
    sum = Abs(s - y);
    return y > s ? 1 : 0;
}
int main() {
    read(n, m, s);
    int L = INF_I32, R = -1, mid;
    i64 ans = INF_I64;
    fp(i, 1, n) {
        read(w[i], v[i]);
        R = Max(R, w[i]);
        L = Min(L, w[i]);
    }
    fp(i, 1, m) read(l[i], r[i]);
    L--;
    R += 2;
    while (L <= R) {
        mid = (L + R) >> 1;
        if (check(mid))
            L = mid + 1;
        else
            R = mid - 1;
        if (sum < ans) ans = sum;
    }
    printf("%lld", ans);
    return 0;
}