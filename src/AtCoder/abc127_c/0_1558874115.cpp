#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int OFFSET = 5, N = 1e5 + OFFSET;
const int MOD = 1e9 + 7;
int d[N];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        ++d[x];
        --d[y + 1];
    }
    int now = 0, ans = 0;
    for (int i = 1; i <= n; ++i)
        if ((now += d[i]) == m) ++ans;
    cout << ans;
    return 0;
}