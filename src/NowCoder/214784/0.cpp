#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const double pi = acos(-1.0);
double alpha[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%lf", alpha + i);
  sort(alpha, alpha + n);
  for (int i = 0; i < n; ++i) alpha[i] = pi / 180 * (360.0 / n * i - alpha[i]);
  sort(alpha, alpha + n);
  double ans = 0;
  for (int i = 0; i < n; ++i) ans += abs(alpha[i] - alpha[n / 2]);
  printf("%.12lf", ans);
  return 0;
}
