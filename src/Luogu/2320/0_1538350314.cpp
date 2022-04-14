#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


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
