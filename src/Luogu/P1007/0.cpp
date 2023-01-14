#include <bits/stdc++.h>
using std::cin;
using std::cout;
int p, n, max, min;
int main() {
  cin >> p >> n;
  for (int i = 1, a; i <= n; ++i) {
    cin >> a;
    max = std::max(max, std::max(a, p - a + 1));
    min = std::max(min, std::min(a, p - a + 1));
  }
  cout << min << ' ' << max;
  return 0;
}
