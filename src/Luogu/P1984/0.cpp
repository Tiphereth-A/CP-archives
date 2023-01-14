#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  double ans = 0.00, now = 420000.00 / n;
  for (int i = 1; i <= n; i++) {
    ans += now;
    now *= (1 - 0.5 / i);
  }
  printf("%.2lf", ans);
  return 0;
}
