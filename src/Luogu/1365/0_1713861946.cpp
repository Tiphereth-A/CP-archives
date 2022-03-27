#include <cstdio>
#ifndef ONLINE_JUDGE
#include <ctime>
#include <iostream>
#endif
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
double a[N], b[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    freopen("D:\\code\\IO\\err.err", "w", stderr);
    clock_t c1 = clock();
#endif
    int n;
    scanf("%d\n", &n);
    _fp(i, 1, n) {
        char c;
        while (((c = getchar()) != 'o') && (c != 'x') && (c != '?'))
            ;
        double p = (c == 'o') ? 1 : (c == 'x' ? 0 : 0.5);
        a[i] = (a[i - 1] + 1) * p;
        b[i] = (2 * a[i - 1] + 1) * p + b[i - 1];
    }
    printf("%.4lf", b[n]);
#ifndef ONLINE_JUDGE
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}