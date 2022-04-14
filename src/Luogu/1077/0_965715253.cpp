#include <bits/stdc++.h>
#if 0
#include <bits/stdc++.h>
#endif
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)

#define tpn typename
#if 0
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define mem(a) memset(a, 0, sizeof(a))
#define memid(a) memset(a, 63, sizeof(a))
#define memax(a) memset(a, 127, sizeof(a))
#define gc getchar
#define sstr stringstream
#endif
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
#define M 105
#define N 1005
const int INF = 0x3f3f3f3f;
const int MOD = 1000007;
int n, m, f[M][M];
int main() {
    scanf("%d%d", &n, &m);
    _for(i, 0, n) f[i][0] = 1;
    _for(i, 1, n) {
        int a;
        scanf("%d", &a);
        _for(j, 0, a)
            _for(k, 0, m - j) {
                if (j == 0 && k == 0) continue;
                f[i][j + k] = (f[i][j + k] + f[i - 1][k]) % MOD;
            }
    }
    printf("%d\n", f[n][m] % MOD);
    return 0;
}