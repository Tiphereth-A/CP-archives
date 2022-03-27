#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#define ll long long
#define rg register
#define il inline
const int maxn = 2000 + 10;
using namespace std;
il int gcd(int x, int y) {
    return x % y == 0 ? y : gcd(y, x % y);
}
int main() {
    int x, y, ans = 0;
    cin >> x >> y;
    int m = x * y;
    for (rg int i = 1; i <= sqrt(m); i++) {
        if (!(m % i) && (gcd(i, m / i) == x)) ans++;
    }
    cout << ans * 2;
    return 0;
}
