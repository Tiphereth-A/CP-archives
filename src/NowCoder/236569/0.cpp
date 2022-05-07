#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t OFFSET = 5;
const uint32_t N = 1e6, M = 2e5 + OFFSET, K = 21;
const uint32_t MOD = 1e9 + 7;
const double EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const pii DIR4[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const pii DIR8[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
double harmony[N + OFFSET];
const double egamma = 0.5772156649015329;
auto __STATIC__ = []() {
    harmony[1] = 1;
    _for(i, 2, N) harmony[i] = harmony[i - 1] + 1.0 / i;
    return 0.0;
}();
#define MULTI_CASES
inline auto solve() -> void {
    int n;
    cin >> n;
    double ans = 0;
    if (n > N)
        ans = log(n);
    else
        ans = harmony[n - 1] - egamma;
    cout << fixed << setprecision(6) << ans << '\n';
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