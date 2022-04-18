#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
#define _foreach_val(i, container) for (auto i : container)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_rref(i, container) for (auto &&i : container)
#define _foreach_iter(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define _foreach_iter_range(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
const int N = 1e7 + 5;
const int ans[5][11] = {
    {},
    {0, 7, 42, 252, 1512, 9072, 54432, 326592, 1959552, 11757312, 70543872},
    {0, 42, 1302, 40362, 1251222, 38787882, 202424335, 275154343, 529784577, 423321775, 122974934},
    {0, 252, 40362, 6464682, 35432335, 842671407, 616154088, 437759359, 327032958, 134696199, 101364960},
    {0, 1512, 1251222, 35432335, 858748060, 475588928, 441649817, 820056146, 163409120, 542623454, 754486763}};
inline auto solve() -> void {
    uint32_t n, m;
    cin >> n >> m;
    cout << ans[n][m];
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