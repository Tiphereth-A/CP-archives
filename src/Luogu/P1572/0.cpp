#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int main() {
  int a, b, c, d;
  scanf("%d/%d", &a, &b);
  while (~scanf("%d/%d", &c, &d)) {
    int m = gcd(b, d);
    (a *= d / m) += c *= b / m;
    b *= d / m;
    m = gcd(a, b);
    a /= m;
    b /= m;
  }
  if (b < 0) {
    a = -a;
    b = -b;
  }
  if (b == 1) printf("%d\n", a);
  else printf("%d/%d\n", a, b);
}
