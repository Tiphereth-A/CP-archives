#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int N = 1e7 + 5;
bool vis[N];
int prime[N], cnt_prime;
int phi[N];
void init(int n = N - 1) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) phi[prime[++cnt_prime] = i] = i - 1;
        for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            phi[i * prime[j]] = phi[i] * prime[j];
            if (i % prime[j] == 0) break;
            phi[i * prime[j]] -= phi[i];
        }
    }
}
i64 qpow(i64 a, i64 b, i64 mod) {
    i64 res = 1;
    a %= mod;
    for (; b; b >>= 1, (a *= a) %= mod)
        if (b & 1) (res *= a) %= mod;
    return res;
}
i64 P[N];
i64 solve(i64 p) {
    if (p == 1) return 0;
    if (P[p]) return P[p];
    return P[p] = qpow(2, solve(phi[p]) + phi[p], p);
}
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    init();
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        int p;
        scanf("%d", &p);
        printf("%lld\n", solve(p));
    __end_kase:;
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}