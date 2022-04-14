#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


#define MAXN 1005
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
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