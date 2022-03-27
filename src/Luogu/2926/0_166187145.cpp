#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int a[N], cnt[N], ans[N];
int main() {
    int n;
    cin >> n;
    int maxn = -1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ++cnt[a[i]];
        maxn = max(maxn, a[i]);
    }
    for (int i = 1; i <= maxn; ++i)
        if (cnt[i])
            for (int j = i; j <= maxn; j += i) ans[j] += cnt[i];
    for (int i = 1; i <= n; ++i) cout << ans[a[i]] - 1 << endl;
    return 0;
}