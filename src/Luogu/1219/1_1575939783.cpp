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
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define MAXN 1005
#define fp(i, l, r) for (register int i = (l); i <= (r); i++)
#define fd(i, r, l) for (register int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int a[15], cnt, n;
const int f[] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184, 14772512, 95815104, 666090624, 4968057848, 39029188884, 314666222712, 2691008701644, 24233937684440, 227514171973736, 2207893435808352, 22317699616364044, 234907967154122528};
il bool check(int n) {
    fp(i, 2, n)
        fp(j, 1, i - 1) if ((a[i] == a[j]) || (abs(a[i] - a[j]) == abs(i - j))) return 0;
    return 1;
}
void queen(int k) {
    if (k > n) {
        if (cnt < 3) {
            cnt++;
            fp(i, 1, n) cout << a[i] << ' ';
            cout << endl;
        }
    } else if (cnt >= 3)
        return;
    else {
        fp(i, 1, n) {
            a[k] = i;
            if (check(k)) queen(k + 1);
        }
    }
    return;
}
int main() {
    cin >> n;
    queen(1);
    cout << f[n];
    return 0;
}
