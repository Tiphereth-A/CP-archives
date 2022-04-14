#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

#define MAXN 1000005
using namespace std;
int main() {
    int n;
    cin >> n;
    int s = ceil(sqrt(n));
    int a, b;
    for (int i = 2; i <= s; i++) {
        if (n % i == 0) {
            a = i;
            b = n / i;
            break;
        }
    }
    cout << ((a > b) ? a : b);
    return 0;
}
