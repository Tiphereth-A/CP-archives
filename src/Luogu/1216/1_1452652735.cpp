#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define MAXN 1005
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
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
