#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  double v = 2, x;
  cin >> x;
  for (double s = 0; s <= x; ++n, s += v, v *= 0.98);
  cout << n;
  return 0;
}
