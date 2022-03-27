#include <algorithm>
#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef long long i64;
i64 l, m, n;
i64 d[50005];
bool inline solve(const i64& len) {
    int cnt = 0, now = 0;
    for (int i = 1; i < n + 1; ++i) {
        if (d[i] - d[now] < len)
            ++cnt;
        else
            now = i;
    }
    if (cnt > m)
        return false;
    else
        return true;
}
int main() {
    scanf("%lld%lld%lld", &l, &n, &m);
    fp(i, 1, n) scanf("%lld", d + i);
    d[n + 1] = l;
    i64 left = 1, right = l, ans = 0;
    while (left <= right) {
        i64 mid = (left + right) >> 1;
        if (solve(mid)) {
            ans = mid;
            left = mid + 1;
        } else
            right = mid - 1;
    }
    printf("%lld", ans);
    return 0;
}