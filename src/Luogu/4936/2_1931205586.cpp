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

#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define rep(i, l, r) for (int i = (l); i < (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define tpn typename
#ifdef __C_LIB__
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 0x3f, sizeof(a))
#define memng(a) memset(a, 0xff, sizeof(a))
#endif
#ifdef __CPP_STYLE__
#define dbg(x) cout << #x << " = " << x << endl
#endif
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
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
#define M 310
#define N 20
#define INF 0x3f3f3f3f
#define INF_I64 0x7FFFFFFFFFFFFFFFll
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
    ans = (n - 1) % MOD;
    for (; n >= 32; n -= 32) ans = (ans << 32) % MOD;
    printf("%llu", ((ans << n) + 1) % MOD);
    return 0;
}