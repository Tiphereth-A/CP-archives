#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
#define MULTI_CASES
inline auto solve() -> void {
    string s;
    cin >> s;
    if (s.size() == 2) {
        cout << s[1] << '\n';
        return;
    }
    char _ = 0x7f;
    int __ = 0;
    _for(i, 0, (int)s.size() - 1) {
        if (_ > s[i]) {
            __ = i;
            _ = s[i];
        }
    }
    cout << _ << '\n';
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