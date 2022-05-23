#include <bits/stdc++.h>
using namespace std;
#define _rfor(i, r, l, vals...) for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
#define MULTI_CASES
void solve() {
    int n, m;
    cin >> n >> m;
    int a, b;
    _rfor(i, int(ceil(sqrt(n))), 1)
        if (n % i == 0) {
            a = i;
            b = n / i;
            break;
        }
    cout << ((a + b) * 2 + 4 <= m ? "Good" : "Miss") << '\n';
}
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
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
FINISHED:
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}