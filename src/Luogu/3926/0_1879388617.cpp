#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

#define MAXN 100010
using namespace std;
int main() {
    int a, c, p, q, r, x;
    cin >> a >> c >> p >> q >> r >> x;
    int t1 = (c - a) * p;
    int t2 = t1 + q;
    if (a <= c) {
        if (x <= t1)
            cout << (x / p + a);
        else if (x <= t2)
            cout << c;
        else
            cout << c + (x - t2) / r;
    } else
        cout << a + x / r;
    return 0;
}
