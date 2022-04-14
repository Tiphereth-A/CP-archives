#include <bits/stdc++.h>
typedef long long ll;
ll ans;
int n, k;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> k;
        ans += k;
    }
    std::cout << ((ans & 1) ? "Alice" : "Bob");
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}