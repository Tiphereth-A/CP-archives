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
int k;
int main() {
    bool f = 1;
    cin >> k;
    _for(i, 10000, 30000)
        if ((i / 100 % k == 0) && (i / 10 % 1000 % k == 0) && (i % 1000 % k == 0)) printf("%d\n", i), f = 0;
    if (f) cout << "No";
    return 0;
}