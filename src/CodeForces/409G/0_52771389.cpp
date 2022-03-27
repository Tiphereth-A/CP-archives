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
double x, y, sum;
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    fp(i, 1, n) {
        cin >> x >> y;
        sum += y;
    }
    sum /= n;
    sum += 5;
    printf("%.3lf", sum);
    return 0;
}
