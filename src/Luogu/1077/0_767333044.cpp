#include <cstdio>
#if 0
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#endif
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define rg register
#define il inline
#define tpn typename
#if 0
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
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
    fp(i, 0, n) f[i][0] = 1;
    fp(i, 1, n) {
        int a;
        scanf("%d", &a);
        fp(j, 0, a) fp(k, 0, m - j) {
            if (j == 0 && k == 0) continue;
            f[i][j + k] = (f[i][j + k] + f[i - 1][k]) % MOD;
        }
    }
    printf("%d\n", f[n][m] % MOD);
    return 0;
}