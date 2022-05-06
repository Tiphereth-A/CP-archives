#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
int cnt[256];
inline auto solve() -> void {
    char ch;
    int n;
    cin >> n;
    _for(i, 1, n) {
        cin >> ch;
        ++cnt[ch];
    }
    int ans = 0;
    char anch = 0;
    _for(i, 0, 255) {
        if (cnt[i] > ans) {
            ans = cnt[anch = i];
        }
    }
    cout << anch;
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