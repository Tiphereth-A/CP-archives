#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  while (kase--) {
    i64 Z;
    cin >> Z;
    i64 a = (Z - 1867216.25) / 36524.25;
    i64 A = Z < 2299161 ? Z : Z + 1 + a - floor(a * .25), B, C, D, E;
    i64 k = 0;
    i64 year = 0, month = 0, day = 0;
    for (; day < 1; --A, ++k) {
      D = (C = ((B = A + 1524) - 122.1) / 365.25) * 365.25;
      E = (B - D) / 30.6001;
      day = B - D - floor(E * 30.6001);
    }
    month = E - (E < 14 ? 1 : 13);
    year = C - 4715 - (month > 2);
    if (day == -k) day = 1;
    cout << day << ' ' << month << ' ';
    if (year >= 1) cout << year << '\n';
    else cout << 1 - year << " BC\n";
  }
  return 0;
}
