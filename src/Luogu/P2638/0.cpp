#include <bits/stdc++.h>
using namespace std;
unsigned long long c[105][105];
int main() {
  for (int i = 0; i <= 100; ++i) {
    c[i][i] = c[i][0] = 1;
    for (int j = 1; j < i; ++j) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }
  int n, a, b;
  cin >> n >> a >> b;
  unsigned long long ans = 0;
  for (int i = 0; i <= a; ++i)
    for (int j = 0; j <= b; ++j)
      ans += c[n + i - 1][n - 1] * c[n + j - 1][n - 1];
  cout << ans;
}
