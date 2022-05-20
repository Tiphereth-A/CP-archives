#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const uint32_t MOD = 1e9 + 7;
const double EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr auto __STATIC__ = []() { return 0.0; }();
#define MULTI_CASES
inline auto solve() -> void {
    i64 a, b, c;
    cin >> a >> b >> c;
    cout << a + b + c << " " << b + c << " " << c << '\n';
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