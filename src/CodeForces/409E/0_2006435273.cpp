#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;


#define maxn 405
#define sstr stringstream
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    double n;
    cin >> n;
    _for(a, 1, 10)
        _for(h, 1, 10)
            if (abs(n - (a * h / sqrt(a * a + 4 * h * h))) <= 1e-6) {
                cout << a << ' ' << h << endl;
                return 0;
            }
    return 0;
}
