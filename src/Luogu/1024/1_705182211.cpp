#include <bits/stdc++.h>
using std::cin;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    double a, b, c, d;
    cin >> a >> b >> c >> d;
    double as = b * b - 3 * a * c,
           bs = b * c - 9 * a * d;
    double t = (2 * as * b - 3 * a * bs) / (2 * sqrt(as * as * as));
    double si = acos(t);
    double x1 = (-b - 2 * sqrt(as) * cos(si / 3)) / (3 * a),
           x2 = (-b + sqrt(as) * (cos(si / 3) + sqrt(3) * sin(si / 3))) / (3 * a),
           x3 = (-b + sqrt(as) * (cos(si / 3) - sqrt(3) * sin(si / 3))) / (3 * a);
    printf("%.2f %.2f %.2f", x1, x3, x2);
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}