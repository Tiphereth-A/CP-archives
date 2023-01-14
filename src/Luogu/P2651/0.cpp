#include <bits/stdc++.h>
using namespace std;
i64 gcd(i64 a, i64 b) { return b == 0 ? a : gcd(b, a % b); }
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    i64 a, b;
    cin >> n >> a >> b;
    b /= gcd(a, b);
    for (int i = 3; i <= n; ++i) {
      cin >> a;
      b /= gcd(a, b);
    }
    cout << (b == 1 ? "Yes" : "No") << endl;
  }
  return 0;
}
