#include <bits/stdc++.h>
using namespace std;
int gcd(int x, int y) { return x % y == 0 ? y : gcd(y, x % y); }
int main() {
  int m, a, b;
  cin >> m;
  m <<= 1;
  for (a = sqrt(m); a > 1; a--) {
    b = m / a;
    if (!(m % a) && ((a + b) & 1))
      cout << (b - a + 1) / 2 << " " << (a + b - 1) / 2 << endl;
  }
  return 0;
}
