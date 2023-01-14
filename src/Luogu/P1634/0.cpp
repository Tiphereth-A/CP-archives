#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;
ull x, n;
ull ksm(ull x, ull y) {
  ull ans = 1;
  while (y) {
    if (y & 1) ans *= x;
    x *= x;
    y >>= 1;
  }
  return ans;
}
int main() {
  cin >> x >> n;
  cout << ksm(x + 1, n);
  return 0;
}
