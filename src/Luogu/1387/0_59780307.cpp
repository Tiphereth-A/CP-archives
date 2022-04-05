#include <cstdio>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#define ctn continue
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define gc getchar
#define tpn typename
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline A Min(const A &x, const A &y) {
    return x < y ? x : y;
}
const int N = 205;
int n, m, a[N][N], f[N][N], ans;
int main() {
    scanf("%d%d", &n, &m);
    fp(i, 1, n) fp(j, 1, m) scanf("%d", &a[i][j]);
    fp(i, 1, n) fp(j, 1, m) {
        if (a[i][j] == 0) ctn;
        f[i][j] = Min(Min(f[i - 1][j], f[i][j - 1]), f[i - 1][j - 1]) + 1;
    }
    fp(i, 1, n) fp(j, 1, m) ans = Max(ans, f[i][j]);
    printf("%d\n", ans);
    return 0;
}
