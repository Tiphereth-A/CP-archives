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
int main() {
    ios::sync_with_stdio(false);
    double n;
    cin >> n;
    fp(a, 1, 10) fp(h, 1, 10) if (abs(n - (a * h / sqrt(a * a + 4 * h * h))) <= 1e-6) {
        cout << a << ' ' << h << endl;
        return 0;
    }
    return 0;
}
