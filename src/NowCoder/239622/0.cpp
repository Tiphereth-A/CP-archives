#include <bits/stdc++.h>
using namespace std;
using ld = long double;
pair<ld, int> _[114514];
const ld pi = acos(-1.);
int main() {
  _[4] = {1. / 3, 4};
  _[6] = {sqrt(2) * .5, 8};
  ld _2 = sqrt(3) / 6;
  _[8] = {sqrt(2 * _2 * _2 * (1 - cos(2 * atan(sqrt(2))))), 6};
  _[20] = {sqrt(2 * _2 * _2 * (1 - cos(2 * atan((sqrt(5) - 1) * .5 + 2)))), 12};
  _2 = .5 * tan(.3 * pi);
  _[12] = {sqrt(2 * _2 * _2 * (1 - cos(2 * atan((sqrt(5) - 1) * .5 + 1)))), 20};
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    ld a;
    cin >> n >> a >> k;
    if (!_[n].second) {
      cout << "impossible\n";
      continue;
    }
    cout << "possible " << _[n].second << ' ' << fixed << setprecision(12)
         << a * _[n].first << '\n';
  }
  return 0;
}
