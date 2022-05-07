#include <bits/stdc++.h>
using namespace std;
int main() {
    int kase;
    cin >> kase;
    while (kase--) {
        int n, k;
        cin >> n >> k;
        cout << (k / (n - 1)) * n + k % (n - 1) - (k % n == 0) << endl;
    }
    return 0;
}