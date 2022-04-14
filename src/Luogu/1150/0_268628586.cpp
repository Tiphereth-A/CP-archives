#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

#define MAXN 10010
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    cout << n + (n - 1) / (k - 1);
    return 0;
}