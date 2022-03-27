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
#define maxn 405
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int f[35][35];
int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    f[1][0] = 1;
    fp(i, 1, m) {
        f[1][i] = f[2][i - 1] + f[n][i - 1];
        fp(j, 2, n - 1) f[j][i] = f[j - 1][i - 1] + f[j + 1][i - 1];
        f[n][i] = f[n - 1][i - 1] + f[1][i - 1];
    }
    cout << f[1][m];
    return 0;
}
