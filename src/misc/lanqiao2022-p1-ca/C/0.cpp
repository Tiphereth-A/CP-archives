#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int a[N];
long long s[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + a[i];
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += a[i] * (s[n] - s[i]);
    cout << ans;
}
