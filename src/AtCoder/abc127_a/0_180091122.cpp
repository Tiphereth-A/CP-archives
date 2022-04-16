#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int OFFSET = 5, N = 2e3 + OFFSET;
const int MOD = 1e9 + 7;
int main() {
    int a, b;
    cin >> a >> b;
    cout << (a <= 5 ? 0 : a <= 12 ? b / 2 :
                                    b);
    return 0;
}