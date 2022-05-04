#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
inline int f(i64 x) {
    if (!x) return 1;
    int ans = 0;
    while (x) {
        i64 now = x % 10;
        if (now == 0 || now == 6 || now == 9)
            ++ans;
        else if (now == 8)
            ans += 2;
        x /= 10;
    }
    return ans;
}
#define MULTI_CASES
inline auto solve() -> void {
    i64 n, k;
    cin >> n >> k;
    if (k == 0) {
        cout << n << '\n';
        return;
    }
    if (n < 0) n = -n;
    while (k && (n = f(n))) --k;
    if (k == 0)
        cout << n << '\n';
    else
        cout << ((k + 1) % 2) << '\n';
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