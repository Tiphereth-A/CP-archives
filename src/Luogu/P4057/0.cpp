#include <bits/stdc++.h>
using namespace std;
i64 gcd(i64 a, i64 b) { return b == 0 ? a : gcd(b, a % b); }
int main() {
  i64 a, b, c;
  cin >> a >> b >> c;
  i64 lcm = a * b / gcd(a, b);
  cout << lcm * c / gcd(lcm, c);
  return 0;
}
