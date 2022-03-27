#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define M 2005
int c[M][M], s[M][M], t, k;
int main() {
    scanf("%d%d", &t, &k);
    c[0][0] = c[1][0] = c[1][1] = 1;
    fp(i, 2, 2004) {
        c[i][0] = 1;
        fp(j, 1, i) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            if (c[i][j] >= k) c[i][j] %= k;
        }
    }
    fp(i, 1, 2004) fp(j, 1, 2004) {
        s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        if (i > j && !c[i][j]) ++s[i][j];
    }
    while (t--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", s[x][y]);
    }
    return 0;
}