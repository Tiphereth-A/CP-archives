#include <bits/stdc++.h>
int stat(int num, int digit) {
    int ans = 0;
    for (; num; num /= 10) {
        ans += (num % 10) == digit;
    }
    return ans;
}
int main() {
#ifdef _LOCAL_
    clock_t c1 = clock();
#endif
    int n, x;
    long long ans = 0;
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        ans += stat(i, x);
    }
    std::cout << ans;
#ifdef _LOCAL_
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}