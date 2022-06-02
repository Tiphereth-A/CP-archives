#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _run_return_void(expressions) \
    {                                 \
        expressions;                  \
        return;                       \
    }
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
constexpr auto __STATIC__ = []() { return 0.0; }();
#define MULTI_CASES
inline auto solve() -> void {
    i64 n, m;
    cin >> n >> m;
    if (n == 0) _run_return_void(cout << "0\n");
    cout << max(i64(2), (i64)(ceil(2.0 * n / m))) << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef MULTI_CASES
    int _t;
    cin >> _t;
    while (_t--)
#endif
        solve();
    return 0;
}