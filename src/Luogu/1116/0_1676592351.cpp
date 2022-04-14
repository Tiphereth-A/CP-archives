#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;


#define maxn 10010
using namespace std;
int main() {
    int n;
    cin >> n;
    int a[maxn], ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
                ans++;
            }
    cout << ans;
    return 0;
}
