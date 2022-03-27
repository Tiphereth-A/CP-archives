#include <cstdio>
#define fp(i, l, r) for (register int(i) = (l); (i) <= (r); (i)++)
#define fd(i, l, r) for (register int(i) = (l); (i) >= (r); (i)--)
#define Abs(x) (((x) > 0) ? (x) : -(x))
const double EPS = 1E-8;
int n;
double a[105][105];
inline void Swap(double& a, double& b) {
    double tmp = a;
    a = b;
    b = tmp;
}
int main() {
    scanf("%d", &n);
    fp(i, 1, n) fp(j, 1, n + 1)
        scanf("%lf", &a[i][j]);
    fp(i, 1, n) {
        int m = i;
        fp(j, i, n) if (Abs(a[j][i] - a[m][i]) <= EPS)
            m = j;
        if (m != i)
            fp(j, 1, n + 1) Swap(a[m][j], a[i][j]);
        if (Abs(a[i][i]) <= EPS) {
            printf("No Solution\n");
            return 0;
        }
        fp(j, i + 1, n) {
            double tmp = a[j][i] / a[i][i];
            fp(k, i, n + 1) a[j][k] -= a[i][k] * tmp;
        }
    }
    fd(i, n, 1) {
        fp(j, i + 1, n) a[i][n + 1] -= a[i][j] * a[j][n + 1];
        a[i][n + 1] /= a[i][i];
    }
    fp(i, 1, n) printf("%.2lf\n", a[i][n + 1]);
    return 0;
}