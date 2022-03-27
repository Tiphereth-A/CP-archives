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
    int n;
    cin >> n;
    int a[maxn], ans = 0;
    for (rg int i = 1; i <= n; i++) cin >> a[i];
    for (rg int i = 1; i <= n; i++)
        for (rg int j = i + 1; j <= n; j++)
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
                ans++;
            }
    cout << ans;
    return 0;
}
