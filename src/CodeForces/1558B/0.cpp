#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
const uint32_t OFFSET = 5;
const uint32_t N = 4e6 + OFFSET;
i64 f[N], sum_f[N];
inline auto solve() -> void {
    i64 n, m;
    cin >> n >> m;
    sum_f[n] = f[n] = 1;
    _rfor(i, n - 1, 1) {
        f[i] = sum_f[i + 1];
        for (i64 j = 2; i * j <= n; ++j) f[i] += sum_f[i * j] + m - sum_f[min((i + 1) * j, n + 1)];
        sum_f[i] = (sum_f[i + 1] + f[i]) % m;
    }
    cout << f[1] % m;
}
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
#ifdef _LOCAL_
    std::clog << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _CLOCK_ST).count() << " ms" << std::endl;
#endif
    return 0;
}