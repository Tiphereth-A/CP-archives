#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 21;
int cnt[N] = {1};
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n;
    cin >> n;
    int state = 0;
    long long ans = 0;
    for (int i = 1, _; i <= n; ++i) {
        cin >> _;
        ans += cnt[state ^= (1 << _)]++;
    }
    cout << ans;
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}