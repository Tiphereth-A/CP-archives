#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int a[N];
bool vis[N];
vector<tuple<int, int, int>> op;
inline void solve() {
    int n, q;
    cin >> n;
    _for(i, 1, n) cin >> a[i];
    cin >> q;
    op.reserve(q);
    int now_max = 0;
    _for(i, 1, q, x, y, z) {
        cin >> x >> y;
        if (x == 1) cin >> z;
        op.emplace_back(x, y, z);
    }
    for (auto it = op.rbegin(); it != op.rend(); ++it)
        if (get<0>(*it) == 1) {
            if (!vis[get<1>(*it)]) {
                vis[get<1>(*it)] = 1;
                a[get<1>(*it)] = max(now_max, get<2>(*it));
            }
        } else
            chkmax(now_max, get<1>(*it));
    _for(i, 1, n) cout << (vis[i] ? a[i] : max(now_max, a[i])) << " \n"[i == n];
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
    std::cerr << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _CLOCK_ST).count() << " ms" << std::endl;
#endif
    return 0;
}