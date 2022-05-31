#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
constexpr auto __STATIC__ = []() { return 0.0; }();
#define MULTI_CASES
inline auto solve() -> void {
    int n;
    cin >> n;
    int pre, cnt = 1;
    cin >> pre;
    bool f = 0;
    vector<int> ans;
    ans.reserve(n);
    _for(i, 2, n, x) {
        cin >> x;
        if (f) continue;
        if (x == pre) {
            ++cnt;
            continue;
        }
        if (f |= cnt < 2) continue;
        ans.push_back(i - 1);
        _for(j, i - cnt, i - 2) ans.push_back(j);
        pre = x;
        cnt = 1;
    }
    if (cnt < 2 || f) {
        cout << "-1\n";
        return;
    }
    ans.push_back(n);
    _for(j, n - cnt + 1, n - 1) ans.push_back(j);
    for (int i : ans) cout << i << ' ';
    cout << '\n';
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