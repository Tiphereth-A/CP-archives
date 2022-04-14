#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <bits/stdc++.h>
#endif
const int mod = 1e9 + 7;
long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res % mod;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    freopen("D:\\code\\IO\\err.err", "w", stderr);
    clock_t c1 = clock();
#endif
    long long w, n, k;
    scanf("%lld%lld%lld", &w, &n, &k);
    printf("%lld", w * qpow(qpow(2, k), mod - 2) % mod);
#ifndef ONLINE_JUDGE
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}
