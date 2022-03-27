#include <cmath>
#include <ctime>
#include <iostream>
const int N = 2e4 + 5;
inline bool prime(int n) {
    register int i = 2;
    while (i <= sqrt(n))
        if (!(n % i++))
            return false;
    return true;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    freopen("D:\\code\\IO\\err.err", "w", stderr);
    clock_t c1 = clock();
#endif
    int n;
    std::cin >> n;
    for (int i = 2; i <= sqrt(n); ++i) {
        for (int j = 2; j <= sqrt(n - i); ++j) {
            int k = n - i - j;
            if (prime(i) && prime(j) && prime(k)) {
                std::cout << i << ' ' << j << ' ' << k;
                return 0;
            }
        }
    }
#ifndef ONLINE_JUDGE
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}