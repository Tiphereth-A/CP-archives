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
#ifdef __CPP_STYLE__
#include <bits/stdc++.h>
#endif
#ifdef __CPP_LIB__
#include <bits/stdc++.h>
#endif
#ifdef __STL__
#include <bits/stdc++.h>
#endif
#ifdef __STD__
using namespace std;
#endif
#ifdef __DEF__
#define tpn typename
#ifdef __C_LIB__
#endif
#ifdef __CPP_STYLE__
#endif
#endif
#ifndef tpn
#define tpn typename
#endif
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