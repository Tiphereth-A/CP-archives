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
    int m, a, b;
    cin >> m;
    m <<= 1;
    for (a = sqrt(m); a > 1; a--) {
        b = m / a;
        if (!(m % a) && ((a + b) & 1)) cout << (b - a + 1) / 2 << " " << (a + b - 1) / 2 << endl;
    }
    return 0;
}
