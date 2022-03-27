#include <algorithm>
#include <ctime>
#include <iostream>
const int N = 1e5 + 5;
int n, k;
long long f[N] = {1};
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j >= std::max(0, i - k); --j)
            (f[i] += f[j]) %= 100003;
    }
    std::cout << f[n];
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}