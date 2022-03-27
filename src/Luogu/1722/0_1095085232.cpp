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
#define MAXN 105
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
ll h[MAXN][MAXN];
int main() {
    int n;
    cin >> n;
    fp(i, 0, n) h[0][i] = 1;
    fp(i, 1, n) fp(j, i, n) {
        if (i == j)
            h[i][j] = h[i - 1][j];
        else
            h[i][j] = h[i - 1][j] + h[i][j - 1];
        h[i][j] %= 100;
    }
    cout << h[n][n];
    return 0;
}