#include <bits/stdc++.h>
using namespace std;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    cin >> kase;
    while (kase--) {
        long long m, n;
        cin >> m >> n;
        cout << (1ll + m * n) / 2 << endl;
    __end_kase:;
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}