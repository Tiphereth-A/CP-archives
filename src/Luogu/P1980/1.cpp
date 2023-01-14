#include <bits/stdc++.h>
using namespace std;
int main() {
  int x, j;
  long long n, m, ans = 0;
  cin >> n >> x;
  for (int i = 1; i <= n; i++) {
    m = i;
    while (m != 0) {
      j = m % 10;
      m /= 10;
      if (j == x) ans++;
    };
  };
  cout << ans;
  return 0;
}
