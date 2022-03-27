#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define MOD(x, p) ((x) % (p))
#define N 100005
#define P 10007
int cnt[2][N], sum[2][N];
int num[N], color[N];
int ans;
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    fp(i, 1, n) scanf("%d", num + i);
    fp(i, 1, n) {
        scanf("%d", color + i);
        ++cnt[i & 1][color[i]];
        sum[i & 1][color[i]] = MOD(sum[i & 1][color[i]] + num[i], P);
    }
    fp(i, 1, n) {
        ans = MOD(ans + MOD(i * MOD(MOD((cnt[i & 1][color[i]] - 2) * num[i], P) + sum[i & 1][color[i]], P), P), P);
    }
    printf("%d", ans);
    return 0;
}