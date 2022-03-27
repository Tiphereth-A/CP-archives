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
#define MAXN 105
using namespace std;
int n, k, ans;
void dfs(int rn, int rk, int sum) {
    if (rk == k) {
        if (sum == n) ans++;
        return;
    }
    int m = (n - sum) / (k - rk) + 1;
    for (int i = rn; i <= m; i++) dfs(i, rk + 1, sum + i);
    return;
}
int main() {
    cin >> n >> k;
    dfs(1, 0, 0);
    cout << ans;
    return 0;
}
