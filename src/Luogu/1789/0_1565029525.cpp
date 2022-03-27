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
#define M 10005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define nos(a, b, n) ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int g[M][M], n, m, k, x, y, ans;
il int getint() {
    int t = 0;
    char c = gc();
    while (c < 48 || c > 57) c = gc();
    while (c >= 48 && c <= 57) {
        t = t * 10 + c - 48;
        c = gc();
    }
    return t;
}
int main() {
    n = gi(), m = gi(), k = gi();
    fp(i, 1, m) {
        x = gi();
        y = gi();
        fp(a, -2, 2)
            fp(b, -2, 2) if ((abs(a) + abs(b) <= 2) && nos(a + x, b + y, n))++ g[a + x][b + y];
    }
    fp(i, 1, k) {
        x = gi();
        y = gi();
        fp(a, -2, 2)
            fp(b, -2, 2) if (nos(a + x, b + y, n))++ g[a + x][b + y];
    }
    fp(x, 1, n)
        fp(y, 1, n) ans += (g[x][y] == 0);
    cout << ans;
    return 0;
}
