#include <iostream>
using namespace std;
typedef long long i64;
int main() {
    int t;
    cin >> t;
    while (t--) {
        i64 n;
        cin >> n;
        cout << n - 1 + (n == 4 || n == 10) * 2 << endl;
    }
    return 0;
}