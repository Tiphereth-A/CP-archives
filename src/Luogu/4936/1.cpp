#define __C_STYLE__
#define __C_LIB__
#define __STL__
#define __DEF__
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
#ifdef __C_LIB__
#endif
#endif
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
const int MOD = 1e9 + 7;
u64 ans;
i64 n;
int main() {
    scanf("%lld", &n);
    if (n == 1) {
        puts("0");
        return 0;
    }
    --n;
    ans = n - 1;
    for (; n >= 16; n -= 16) ans = (ans << 16) % MOD;
    printf("%llu", ((ans << n) + 1) % MOD);
    return 0;
}