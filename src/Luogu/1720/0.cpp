#include <bits/stdc++.h>
long long a, b = 1, c = 1;
int main() {
#ifdef _LOCAL_
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
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time:" << clock() - c1 << std::endl;
#endif
    return 0;
}