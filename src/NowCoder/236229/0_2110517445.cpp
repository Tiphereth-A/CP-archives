#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 1e5 + 5;
const double EPS = 1e-6;
struct {
    int x, y;
} points[N];
#define MULTI_CASES
inline auto solve() -> void {
    int a, b, n;
    double k;
    cin >> a >> b >> n >> k;
    _for(i, 1, n) cin >> points[i].x >> points[i].y;
    double _a = a, _b, _k;
    if ((k - 1) < EPS) {
        _b = tan(asin(k)) * _a;
        if ((_b - b) < EPS) {
            cout << "YES\n";
            return;
        }
        _b = b;
        _k = tan(asin(_b / sqrt(a * a + b * b) / k));
    } else {
        _b = b;
        _k = tan(asin(_b / sqrt(a * a + b * b) / k));
    }
    _b = _b - _k * _a;
    _for(i, 1, n)
        if (double __ = points[i].y - _k * points[i].x - _b; __ > EPS) {
            cout << "NO\n";
            return;
        }
    cout << "YES\n";
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
