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
#define maxn 1000005
using namespace std;
int main() {
    int n;
    cin >> n;
    double ans = 0.00, now = 420000.00 / n;
    for (int i = 1; i <= n; i++) {
        ans += now;
        now *= (1 - 0.5 / i);
    }
    printf("%.2lf", ans);
    return 0;
}
