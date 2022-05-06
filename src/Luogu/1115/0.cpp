#include <bits/stdc++.h>
int main() {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    int n;
    std::cin >> n;
    long long ans = 0x8000000000000000, sum = 0;
    for (int tmp, i = 1; i <= n; ++i) {
        std::cin >> tmp;
        ans = std::max(ans, sum += tmp);
        sum = std::max(sum, 0ll);
    }
    std::cout << ans;
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}