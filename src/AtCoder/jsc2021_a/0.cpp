#include <bits/stdc++.h>
using namespace std;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int x, y, z;
    cin >> x >> y >> z;
    if ((z * y) % x == 0) {
        cout << y * z / x - 1;
        return 0;
    }
    cout << floor(1.0 * y / x * z);
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}