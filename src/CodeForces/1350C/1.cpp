#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
int a[N], pre[N], suf[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    pre[1] = a[1];
    suf[n] = a[n];
    for (int i = 2; i <= n; ++i) pre[i] = gcd(pre[i - 1], a[i]);
    for (int i = n - 1; i; --i) suf[i] = gcd(suf[i + 1], a[i]);
    long long ans = lcm(suf[2], pre[n - 1]);
    for (int i = 2; i < n; ++i) ans = lcm(ans, gcd(pre[i - 1], suf[i + 1]));
    cout << ans;
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}