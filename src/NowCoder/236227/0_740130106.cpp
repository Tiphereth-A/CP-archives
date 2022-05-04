#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 1e5 + 5, MOD = 114514919810;
string p[N];
inline auto solve() -> void {
    int n;
    cin >> n;
    string s;
    int id;
    _for(i, 1, n) {
        cin >> s >> id;
        p[id] = s;
    }
    _for(i, 1, n)
        cout << p[i] << " \n"[p[i] == "." || p[i] == "!"];
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