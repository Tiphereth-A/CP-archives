#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 2e7 + 5, P = 1.5e6 + 5;
bool vis[N];
int prime[P], cnt_prime;
uint8_t prime_factor_cnt[N];
inline void init_prime(const int &n = N - 1) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            prime[++cnt_prime] = i;
            prime_factor_cnt[i] = 1;
        }
        for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            prime_factor_cnt[i * prime[j]] = prime_factor_cnt[i];
            if (i % prime[j] == 0) break;
            ++prime_factor_cnt[i * prime[j]];
        }
    }
}
inline i64 calc(i64 x, i64 y, i64 k2) {
    if ((k2 + y) % x) return 0;
    return i64(1) << prime_factor_cnt[(k2 + y) / x];
}
#define MULTI_CASES
inline auto solve() -> void {
    i64 x, y, k;
    cin >> x >> y >> k;
    if (k % gcd(x, y)) {
        cout << "0\n";
        return;
    }
    i64 ans = 0;
    _for(i, 1, (int)sqrt(k)) {
        if (k % i) continue;
        ans += calc(x, y, k / i);
        if (i != k / i) ans += calc(x, y, i);
    }
    cout << ans << '\n';
}
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init_prime();
#ifdef MULTI_CASES
    int _t;
    cin >> _t;
    while (_t--)
#endif
        solve();
#ifdef _LOCAL_
    std::clog << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _CLOCK_ST).count() << " ms" << std::endl;
#endif
    return 0;
}