#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 5e3 + 5;
pair<i64, i64> a[N];
i64 f[N], g[N];
int main() {
    int n, k;
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= k; ++i) scanf("%lld%lld", &a[i].second, &a[i].first);
    sort(a + 1, a + 1 + k);
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= n; ++j) g[j] = f[j - 1] + a[i].first * abs(a[i].second - j);
        for (int j = i; j <= n; ++j) f[j] = i != j ? min(f[j - 1], g[j]) : g[j];
    }
    printf("%lld", f[n]);
}
