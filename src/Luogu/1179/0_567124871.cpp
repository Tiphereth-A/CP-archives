#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#define ll long long
#define ull unsigned long long
#define rg register
#define il inline
#define maxn 10010
using namespace std;
int main() {
    int t, l, r, ans = 0;
    cin >> l >> r;
    for (rg int i = l; i <= r; i++) {
        t = i;
        while (t) {
            if (t % 10 == 2) ans++;
            t /= 10;
        }
    }
    cout << ans;
    return 0;
}