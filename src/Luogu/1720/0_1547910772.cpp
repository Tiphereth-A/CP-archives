#include <ctime>
#include <iostream>
long long a, b = 1, c = 1;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\code\\IO\\in.in", "r", stdin);
    freopen("D:\\code\\IO\\out.out", "w", stdout);
    clock_t c1 = clock();
#endif
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        a = b;
        b = c;
        c = a + b;
    }
    std::cout << a << ".00";
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}