#include <bits/stdc++.h>
using namespace std;
int main() {
  int n = 0, k;
  cin >> k;
  for (double s = 0; s <= k; ++n, s += 1.0 / n);
  cout << n;
  return 0;
}
