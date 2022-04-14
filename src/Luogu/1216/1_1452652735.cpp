#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


#define MAXN 1005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
ll f[MAXN][MAXN];
int main() {
    int r, ans = 0;
    cin >> r;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= i; j++)
            cin >> f[i][j];
    for (int i = 2; i <= r; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] += max(f[i - 1][j], f[i - 1][j - 1]);
    for (int i = 1; i <= r; i++) ans = max(ans, f[r][i]);
    cout << ans;
    return 0;
}
