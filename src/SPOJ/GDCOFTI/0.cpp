#include <algorithm>
#include <cmath>
#include <iostream>
typedef unsigned long long ull;
using namespace std;
ull a, b, c;
int main() {
  cin >> a >> b >> c;
  printf("%lld", __gcd(a, __gcd(b, c)));
  return 0;
}
