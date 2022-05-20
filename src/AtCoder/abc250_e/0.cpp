#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_continue(expressions) \
    {                              \
        expressions;               \
        continue;                  \
    }
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const uint32_t MOD = 1e9 + 7;
const double EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const pii DIR4[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const pii DIR8[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const int FACT[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
constexpr auto __STATIC__ = []() { return 0.0; }();
int unq_cnt_a[N], unq_cnt_b[N];
vector<int> unq_a, unq_b;
set<int> s;
#define __init__(x)                                                    \
    unq_##x.reserve(n);                                                \
    _for(i, 1, n, _) {                                                 \
        cin >> _;                                                      \
        s.insert(_);                                                   \
        unq_cnt_##x[i] = s.size();                                     \
        if (unq_cnt_##x[i] > unq_cnt_##x[i - 1]) unq_##x.push_back(_); \
    }
bool ans[N];
auto __ins__ = [](int x) {
    if (s.count(x))
        s.erase(x);
    else
        s.insert(x);
};
inline auto solve() -> void {
    int n;
    cin >> n;
    __init__(a);
    s.clear();
    __init__(b);
    s.clear();
    _for(i, 1, min(unq_a.size(), unq_b.size())) {
        __ins__(unq_a[i - 1]);
        __ins__(unq_b[i - 1]);
        ans[i] = !s.size();
    }
    int q;
    cin >> q;
    _for(i, 1, q, x, y) {
        cin >> x >> y;
        if (unq_cnt_a[x] != unq_cnt_b[y]) _run_continue(cout << "No\n");
        cout << (ans[unq_cnt_a[x]] ? "Yes\n" : "No\n");
    }
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