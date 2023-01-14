#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int a0, a1, b0, b1;
    cin >> a0 >> a1 >> b0 >> b1;
    int c1 = a0 / a1, c2 = b1 / b0, ans = 0;
    for (int x = 1; x <= sqrt(b1); ++x) {
      if (b1 % x == 0) {
        int now = x;
        if (now % a1 == 0 && gcd(now / a1, c1) == 1 && gcd(b1 / now, c2) == 1)
          ++ans;
        if (x == b1 / x) continue;
        now = b1 / x;
        if (now % a1 == 0 && gcd(now / a1, c1) == 1 && gcd(b1 / now, c2) == 1)
          ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
