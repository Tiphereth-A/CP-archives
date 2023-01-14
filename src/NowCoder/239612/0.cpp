#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const long double PI = acos(-1.l);
int main() {
  int t_;
  cout << fixed << setprecision(12);
  for (cin >> t_; t_; --t_) {
    int n;
    long double r, R;
    cin >> n >> r >> R;
    long double _;
    cin >> _;
    long double r2 = r * r, R2 = R * R, r4 = r2 * r2, rR3 = r * R * R2;
    vector<long double> v;
    v.reserve(n--);
    for (i64 x; n; --n) {
      cin >> x;
      v.push_back(x);
    }
    v.push_back(_ + 2e4);
    for (auto it = v.rbegin(); it != v.rend() - 1; ++it)
      *it = (*it - *(it + 1)) * 5e-5 * PI;
    v.front() = (v.front() - _) * 5e-5 * PI;
    cout << accumulate(v.begin(),
                       v.end(),
                       0.l,
                       [&](long double x, long double i) {
                         return x + (r2 + R2 * .5l) * R2 * i -
                                r4 * tan(i) * (tan(i) * tan(i) + 1) / 6 -
                                rR3 * sin(i) * 4 / 3;
                       }) /
              -accumulate(
                v.begin(),
                v.end(),
                -PI * R2,
                [&](long double x, long double i) { return x + r2 * tan(i); })
         << '\n';
  }
  return 0;
}
