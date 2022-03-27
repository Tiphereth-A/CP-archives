#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define M 30005
#define sstr stringstream
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int f[M], n, m, v[M], p[M];
int main() {
    scanf("%d %d", &n, &m);
    fp(i, 1, m) {
        scanf("%d %d", &v[i], &p[i]);
    }
    fp(i, 1, m) fd(j, n, v[i]) {
        if (j >= v[i])
            f[j] = max(f[j - v[i]] + p[i], f[j]);
    }
    printf("%d", f[n]);
    return 0;
}
