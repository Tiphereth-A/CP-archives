#include <cstring>
#include <ctime>
#include <iostream>
const int N = 1e4 + 5;
bool sum[N];
int n, m;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    freopen("D:\\code\\IO\\err.err", "w", stderr);
    clock_t c1 = clock();
#endif
    std::cin >> n >> m;
    memset(sum, 1, sizeof(bool) * (n + 1));
    while (m--) {
        int x, y;
        std::cin >> x >> y;
        memset(sum + x, 0, sizeof(bool) * (y - x + 1));
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += sum[i];
    }
    std::cout << ans;
#ifndef ONLINE_JUDGE
    std::cerr << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}