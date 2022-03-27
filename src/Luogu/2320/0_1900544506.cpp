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
int money[30];
int main() {
    ll m;
    cin >> m;
    int i = 0, ans = 0;
    for (; m >> 1; m >>= 1)
        money[++ans] = (m >> 1) + (m & 1);
    printf("%d\n1", ans + 1);
    while (ans)
        printf(" %d", money[ans--]);
    return 0;
}
