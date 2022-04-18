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
const int N = 500 + 5;
int f[N][N];
inline auto solve() -> void {
    int n, m;
    cin >> n >> m;
    memset(f, 0x3f, sizeof(f));
    _for(i, 1, n) f[i][i] = 0;
    _for(i, 1, m, x, y, z) {
        cin >> x >> y >> z;
        f[y][x] = f[x][y] = min(f[x][y], z);
    }
    _for(k, 1, n)
        _for(i, 1, n)
            _for(j, 1, n) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    int q;
    cin >> q;
    i64 ans = 0;
    _for(i, 1, q, x, prev = 1) {
        cin >> x;
        if (f[prev][x] == 0x3f3f3f3f) {
            cout << "-1";
            return;
        }
        ans += f[prev][x];
        prev = x;
    }
    cout << ans;
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
