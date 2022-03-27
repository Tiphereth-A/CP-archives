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
#define M 20005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define nos(a, b, n) ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define gi getint
#define gc getchar
using namespace std;
int f[M], n, V, v[35];
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
    V = gi();
    n = gi();
    fp(i, 1, n) v[i] = gi();
    fp(i, 1, n) fd(j, V, 0) if (j - v[i] >= 0) f[j] = max(f[j], f[j - v[i]] + v[i]);
    int ans = 0;
    fp(i, 1, V) ans = max(ans, f[i]);
    cout << V - ans;
    return 0;
}
