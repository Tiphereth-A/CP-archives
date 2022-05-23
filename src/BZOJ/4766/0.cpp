#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
inline constexpr i64 qpow(i64 a, i64 b, const i64 &mod) {
    i64 res(1);
    a %= mod;
    for (; b; b >>= 1, (a *= a) %= mod)
        if (b & 1) (res *= a) %= mod;
    return res;
};
inline auto solve() -> void {
    i64 n, m, p;
    cin >> n >> m >> p;
    cout << qpow(m, n - 1, p) * qpow(n, m - 1, p) % p << '\n';
}
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
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