#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while (cin >> n)
    if (n < 0)
      if (n % 2 == 0) cout << "Underflow!" << endl;
      else cout << "Overflow!" << endl;
    else {
      long long ans = 1;
      for (int i = 1; i <= n; ++i) {
        ans *= i;
        if (ans > 6227020800) break;
      }
      if (ans < 10000) cout << "Underflow!" << endl;
      else if (ans > 6227020800) cout << "Overflow!" << endl;
      else cout << ans << endl;
    }
  return 0;
}
