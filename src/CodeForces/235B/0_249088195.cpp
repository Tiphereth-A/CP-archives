#include <cstdio>
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
double a[N], b[N], p[N];
int main() {
    int n;
    scanf("%d", &n);
    _fp(i, 1, n) {
        scanf("%lf", p + i);
        a[i] = (a[i - 1] + 1) * p[i];
        b[i] = (2 * a[i - 1] + 1) * p[i] + b[i - 1];
    }
    printf("%.9lf", b[n]);
    return 0;
}