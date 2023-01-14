#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const int N = 100;
i128 f[N][N], p[N] = {1};
int a[N];
void print(i128 n) {
  string s;
  while (n) {
    s.push_back(n % 10 + '0');
    n /= 10;
  }
  reverse(s.begin(), s.end());
  if (s.empty()) s = "0";
  cout << s << endl;
}
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i < N; ++i) p[i] = p[i - 1] * 2;
  i128 ans = 0;
  while (n--) {
    for (int i = 1; i <= m; ++i) {
      cin >> a[i];
      f[i][i] = a[i] * p[m];
    }
    for (int len = 2; len <= m; ++len)
      for (int l = 1, r; l <= m - len + 1; ++l) {
        r = l + len - 1;
        f[l][r] = max(f[l][r - 1] + a[r] * p[m - len + 1],
                      f[l + 1][r] + a[l] * p[m - len + 1]);
      }
    ans += f[1][m];
  }
  print(ans);
  return 0;
}
