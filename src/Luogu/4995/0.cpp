#define __DEF__
#define __FASTIO__
#define __FUNC__
#include <bits/stdc++.h>
#ifdef __DEF__
#endif
#ifdef __FUNC__
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
#if 0
#else
namespace fastIO {
#define gc() (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
const int SIZ = 1 << 21 | 1;
char *iS, *iT, ibuff[SIZ], obuff[SIZ], *oS = obuff, *oT = oS + SIZ - 1, fu[110], c;
int fr;
inline void out() {
    fwrite(obuff, 1, oS - obuff, stdout);
    oS = obuff;
}
template <class Type>
inline void read(Type &x) {
    x = 0;
    Type y = 1;
    for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc())
        ;
    c == '-' ? y = -1 : x = (c & 15);
    for (c = gc(); c >= '0' && c <= '9'; c = gc())
        x = x * 10 + (c & 15);
    x *= y;
}
template <class Type, typename... Args>
inline void read(Type &x, Args &...args) {
    read(x);
    read(args...);
}
template <class Type>
inline void print(Type x, char text = '\n') {
    if (x < 0) *oS++ = '-', x *= -1;
    if (x == 0) *oS++ = '0';
    while (x) fu[++fr] = x % 10 + '0', x /= 10;
    while (fr) *oS++ = fu[fr--];
    *oS++ = text;
    out();
}
}  // namespace fastIO
#endif
#endif
const int N = 305;
int h[N];
int n;
u64 ans;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", h + i);
    std::sort(h + 1, h + n + 1, std::greater<int>());
    ans += h[1] * h[1];
    for (int i = 1, j = n; i < j; --j)
        ans += (h[i] - h[j]) * (h[i] - h[j]) + (h[++i] - h[j]) * (h[i] - h[j]);
    printf("%llu", ans);
    return 0;
}