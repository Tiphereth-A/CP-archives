#include <iostream>
using namespace std;
const int maxn = 3e6 + 5;
typedef long long ll;
ll inv[maxn];
int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    inv[1] = 1;
    int n, p;
    cin >> n >> p;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
    for (int i = 1; i <= n; i++)
        cout << inv[i] << '\n';
    return 0;
}