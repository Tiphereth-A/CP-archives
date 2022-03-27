#include <bits/stdc++.h>
using namespace std;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a == b) {
        if (a == 0)
            cout << 0;
        else
            cout << min(c, 2 * d);
    } else {
        if (a == 0 || b == 0)
            cout << d;
        else
            cout << min(c + d, 2 * d);
    }
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}