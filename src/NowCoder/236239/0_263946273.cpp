#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
#define _foreach_val(i, container) for (auto i : container)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_rref(i, container) for (auto &&i : container)
#define _foreach_iter(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define _foreach_iter_range(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
const int N = 2e5 + 5;
int a[N];
inline auto solve() -> void {
    int n;
    cin >> n;
    _for(i, 1, n) cin >> a[i];
    int maxl = 0, nowl = 0;
    _for(i, 1, n) {
        if (a[i] < a[i - 1])
            ++nowl;
        else {
            maxl = max(maxl, nowl);
            nowl = 0;
        }
    }
    maxl = max(maxl, nowl);
    nowl = 0;
    _rfor(i, n, 1) {
        if (a[i] < a[i + 1])
            ++nowl;
        else {
            maxl = max(maxl, nowl);
            nowl = 0;
        }
    }
    cout << max(maxl, nowl);
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
