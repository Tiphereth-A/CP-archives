#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define maxn 100010
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
