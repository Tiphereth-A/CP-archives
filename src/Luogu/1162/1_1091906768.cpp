#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
#define maxn 33
#define ull unsigned long long
#define rg register
#define fp(i, m, n) for (register int i = m; i <= n; i++)
#define fd(i, m, n) for (register int i = m; i >= n; i--)
#define il inline
using namespace std;
int f[maxn][maxn], n;
void dfs(int x, int y) {
    f[x][y] = 2;
    if (x > 0 && y + 1 > 0 && x <= n && y + 1 <= n && f[x][y + 1] == 0)
        dfs(x, y + 1);
    if (x > 0 && y - 1 > 0 && x <= n && y - 1 <= n && f[x][y - 1] == 0)
        dfs(x, y - 1);
    if (x + 1 > 0 && y > 0 && x + 1 <= n && y <= n && f[x + 1][y] == 0)
        dfs(x + 1, y);
    if (x - 1 > 0 && y > 0 && x - 1 <= n && y <= n && f[x - 1][y] == 0)
        dfs(x - 1, y);
    return;
}
int main() {
    int x = 0, y = 0;
    scanf("%d", &n);
    fp(i, 1, n) fp(j, 1, n) {
        scanf("%d", &f[i][j]);
        if (f[i][j] && x == 0) {
            x = i + 1;
            y = j + 1;
        }
    }
    dfs(x, y);
    fp(i, 1, n) {
        fp(j, 1, n)
            printf("%d ", f[i][j]);
        printf("\n");
    }
    return 0;
}