#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
const uint32_t OFFSET = 5;
const uint32_t N = 3e6 + OFFSET;
int a[N], ans[N];
stack<int> monos;
inline void solve() {
    int n;
    cin >> n;
    _for(i, 1, n) cin >> a[i];
    _rfor(i, n, 1) {
        while (!monos.empty() && a[monos.top()] <= a[i]) monos.pop();
        ans[i] = monos.empty() ? 0 : monos.top();
        monos.push(i);
    }
    _for(i, 1, n) cout << ans[i] << " \n"[i == n];
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