#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t N = 500;
constexpr auto __STATIC__ = []() { return 0.0; }();
bool maps[N][N];
inline auto solve() -> void {
    int n;
    cin >> n;
    _for(i, 1, n, x, y) {
        cin >> x >> y;
        maps[x][y] = 1;
    }
    i64 ans = 0;
    _for(i, -500, 500) {
        i64 cnt = 0;
        for (int j = max(1, 1 - i), k = max(1, i + 1); j <= 500 && k <= 500; ++j, ++k) {
            if (!maps[j][k]) {
                ans += cnt * (cnt + 1);
                cnt = 0;
                continue;
            }
            ++cnt;
        }
        ans += cnt * (cnt + 1);
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