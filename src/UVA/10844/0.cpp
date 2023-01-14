#include <bits/stdc++.h>
using namespace std;
typedef vector<char> bint;
bint add(const bint &x, const bint &y) {
  bint z(max((short)x.size(), (short)y.size()) + 1);
  z[0] = 0;
  for (decltype(z.size()) i = 0; i < z.size() - 1; ++i) {
    if (i < x.size()) z[i] += x[i];
    if (i < y.size()) z[i] += y[i];
    z[i + 1] += z[i] / 10;
    z[i] %= 10;
  }
  if ((short)z.size() > 1 && !z.back()) z.pop_back();
  return z;
}
bint b[901][902];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  b[0][1].push_back(1);
  for (int i = 1; i <= 900; ++i)
    for (int j = 1; j <= i + 1; ++j)
      b[i][j] = j == 1 ? b[i - 1][i] : add(b[i][j - 1], b[i - 1][j - 1]);
  int n;
  while (cin >> n && n) {
    cout << n << ", ";
    for (auto it = b[n][1].rbegin(); it != b[n][1].rend(); ++it)
      cout << char(*it + '0');
    cout << '\n';
  }
}
