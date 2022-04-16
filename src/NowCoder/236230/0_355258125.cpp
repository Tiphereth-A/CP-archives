#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
#define _foreach_val(i, container) for (auto i : container)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_rref(i, container) for (auto &&i : container)
#define _foreach_iter(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define _foreach_iter_range(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
const int N = 1e3 + 5;
const double EPS = 1e-6;
const pii DIR8[8] = {{-1, -2}, {-1, 2}, {1, 2}, {1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
int vis[N][N];
bool target[N][N];
pii query[N * N];
auto vaild = [](int x, int y, int n, int m) -> bool {
    return (x >= 1) && (x <= n) && (y >= 1) && (y <= m);
};
// #define MULTI_CASES
inline auto solve() -> void {
    int n, m, q;
    cin >> n >> m >> q;
    int x, y;
    cin >> x >> y;
    _for(i, 1, q, x, y) {
        cin >> x >> y;
        target[x][y] = 1;
        query[i] = {x, y};
    }
    queue<tuple<int, int, int>> pos;
    pos.emplace(x, y, 1);
    vis[x][y] = 1;
    int cnt = 0;
    while (cnt < q && !pos.empty()) {
        auto [x, y, step] = pos.front();
        pos.pop();
        for (auto [dx, dy] : DIR8) {
            if (!vaild(x + dx, y + dy, n, m)) continue;
            if (vis[x + dx][y + dy]) continue;
            if (target[x + dx][y + dy]) ++cnt;
            vis[x + dx][y + dy] = step;
            pos.emplace(x + dx, y + dy, step + 1);
        }
    }
    // _for(i, 1, n)
    //     _for(j, 1, m) cerr << vis[i][j] << " \n"[j == m];
    _for(i, 1, q) cout << (query[i].first == x && query[i].second == y ? 0 : vis[query[i].first][query[i].second] ? vis[query[i].first][query[i].second] :
                                                                                                                    -1)
                       << '\n';
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
