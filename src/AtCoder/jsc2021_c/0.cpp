#include <bits/stdc++.h>
using namespace std;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int a, b;
    cin >> a >> b;
    int ans = 1;
    for (int i = 2, _; i <= b; ++i) {
        _ = ceil(1.0 * a / i);
        if (_ * i >= a && _ * i <= b && (_ + 1) * i >= a && (_ + 1) * i <= b) ans = i;
    }
    cout << ans;
#ifndef ONLINE_JUDGE
    std::cerr
        << "\n---\n"
        << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}