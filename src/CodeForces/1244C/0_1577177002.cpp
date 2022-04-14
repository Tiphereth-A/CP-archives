#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
long long n, p, w, d;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    cin >> n >> p >> w >> d;
    long long x, y = 0;
    while (y < w && (p - y * d) % w)
        ++y;
    if (y == w) {
        cout << -1;
        return 0;
    }
    x = (p - y * d) / w;
    if (x + y > n || x < 0)
        cout << -1;
    else
        cout << x << " " << y << " " << n - x - y;
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}