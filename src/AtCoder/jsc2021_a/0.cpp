#include <bits/stdc++.h>
using namespace std;
int main() {
  int x, y, z;
  cin >> x >> y >> z;
  if ((z * y) % x == 0) {
    cout << y * z / x - 1;
    return 0;
  }
  cout << floor(1.0 * y / x * z);
  return 0;
}
