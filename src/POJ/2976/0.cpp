#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (int i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e3 + OFFSET;
const double EPS = 1e-6;
int n, k;
int a[N], b[N];
double c[N];
bool check(double x) {
  _for(i, 1, n) c[i] = a[i] - x * b[i];
  partial_sort(c + 1, c + k + 1, c + n + 1);
  return accumulate(c + k + 1, c + n + 1, 0.0) > 0;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(0);
  while ((cin >> n >> k), n || k) {
    _for(i, 1, n) cin >> a[i];
    _for(i, 1, n) cin >> b[i];
    double l = 0, r = 1e9, mid;
    while (r - l > EPS) (check(mid = l + (r - l) / 2) ? l : r) = mid;
    cout << 100 * l << '\n';
  }
  return 0;
}
