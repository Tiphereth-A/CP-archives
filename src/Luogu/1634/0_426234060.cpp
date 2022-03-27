#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define MAXN 1005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
ull x, n;
ull ksm(ull x, ull y) {
    ull ans = 1;
    while (y) {
        if (y & 1) ans *= x;
        x *= x;
        y >>= 1;
    }
    return ans;
}
int main() {
    cin >> x >> n;
    cout << ksm(x + 1, n);
    return 0;
}