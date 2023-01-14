#include <bits/stdc++.h>
using namespace std;
const long double EPS = 1e-12;
int main() {
  long long n, k;
  cin >> n >> k;
  long double ans = (n >= k) * (n - k + 1);
  for (int i = 1; i <= min(n, k - 1); ++i)
    for (int j = 17; ~j; --j)
      if ((1ll << j) * i < k) {
        ans += 1.0l / (1 << (j + 1));
        break;
      }
  printf("%.12Lf\n", (ans / n - EPS));
  return 0;
}
