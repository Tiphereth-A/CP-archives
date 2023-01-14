#include <bits/stdc++.h>
using namespace std;
int gcd(int x, int y) { return x % y == 0 ? y : gcd(y, x % y); }
int main() {
  int x, y, ans = 0;
  cin >> x >> y;
  int m = x * y;
  for (int i = 1; i <= sqrt(m); i++) {
    if (!(m % i) && (gcd(i, m / i) == x)) ans++;
  }
  cout << ans * 2;
  return 0;
}
