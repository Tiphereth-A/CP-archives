#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const i64 N = 1e6 + 5, MOD = 114514919810;
i64 f[N];
#define MULTI_CASES
inline auto solve() -> void {
    int n;
    cin >> n;
    cout << f[n] << '\n';
}
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    f[1] = f[2] = 1;
    _for(i, 3, N - 1) f[i] = (f[i - 1] + f[i - 2] + 1) % MOD;
    _for(i, 2, N - 1) f[i] = (f[i] + f[i - 1]) % MOD;
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