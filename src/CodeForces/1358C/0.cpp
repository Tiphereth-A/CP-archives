#include <bits/stdc++.h>
using namespace std;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    cin >> kase;
    while (kase--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        unsigned long long m = x2 - x1, n = y2 - y1;
        cout << m * n + 1 << endl;
    __end_kase:;
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}