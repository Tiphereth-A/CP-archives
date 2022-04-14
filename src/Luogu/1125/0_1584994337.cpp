#include <bits/stdc++.h>
using namespace std;
bool isp(int n) {
    if (n == 2) return true;
    if (n > 2) {
        for (int i = 2; i <= sqrt(n); i++)
            if (n % i == 0) return false;
        return true;
    }
    return false;
}
int main() {
    int a[26] = {0}, maxn = 0, minn = 1000;
    char c;
    while ((c = getchar()) != EOF) a[c - 'a']++;
    for (int i = 0; i < 26; i++) {
        maxn = max(maxn, a[i]);
        if (a[i]) minn = min(minn, a[i]);
    }
    if (isp(maxn - minn))
        cout << "Lucky Word" << endl
             << maxn - minn;
    else
        cout << "No Answer" << endl
             << 0;
    return 0;
}
