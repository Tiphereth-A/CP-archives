#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

#define MAXN 10010
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    int num[MAXN];
    for (int i = 0; i < n; i++)
        cin >> num[i];
    sort(num, num + n);
    int ans = unique(num, num + n) - num;
    if (ans > k)
        cout << num[k - 1];
    else
        cout << "NO RESULT";
    return 0;
}
