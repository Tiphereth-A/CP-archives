#include <cstdio>
#define fp(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2005;
typedef int MAT[N][N];
int m, n, k;
MAT mat, matlu, matld, matru, matrd;
int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int x;
    scanf("%d%d%d", &m, &n, &k);
    fp(i, 1, m) fp(j, 1, n) {
        scanf("%d", &x);
        mat[i][j] = mat[i][j - 1] + mat[i - 1][j] - mat[i - 1][j - 1] + x;
    }
    fd(i, m, k) fd(j, n, k)
        mat[i][j] -= mat[i - k][j] + mat[i][j - k] - mat[i - k][j - k];
    fp(i, k, m) fp(j, k, n)
        matlu[i][j] = max(max(matlu[i - 1][j], matlu[i][j - 1]), mat[i][j]);
    fp(i, k, m) fd(j, n, k)
        matru[i][j] = max(max(matru[i - 1][j], matru[i][j + 1]), mat[i][j]);
    fd(i, m, k) fp(j, k, n)
        matld[i][j] = max(max(matld[i + 1][j], matld[i][j - 1]), mat[i][j]);
    fd(i, m, k) fd(j, n, k)
        matrd[i][j] = max(max(matrd[i + 1][j], matrd[i][j + 1]), mat[i][j]);
    int maxn = -1;
    fp(i, k, m - k) fp(j, k, n - k)
        maxn =
            max(maxn,
                max(max(matlu[i][j] + matru[i][j + k] + matld[i + k][n],
                        matlu[i][n] + matld[i + k][j] + matrd[i + k][j + k]),
                    max(matrd[i + k][j + k] + matru[i][j + k] + matlu[i][j],
                        matlu[m][j] + matrd[i + k][j + k] + matru[i][j + k])));
    fp(i, k, m - k) fp(j, k * 2, n - k)
        maxn = max(maxn, matlu[m][j - k] + matru[m][j + k] + mat[i][j]);
    fp(i, k * 2, m - k) fp(j, k, n - k)
        maxn = max(maxn, matlu[i - k][n] + matld[i + k][n] + mat[i][j]);
    printf("%d", maxn);
    return 0;
}