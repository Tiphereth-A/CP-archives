#include <bits/stdc++.h>
using namespace std;
const char ch[] = "NO\0YES";
int main() {
  int n, m, k;
  cin >> n >> m >> k;
  int flag = 0;
  for (int i = 1, x, y; i <= k; ++i) {
    cin >> x >> y;
    flag |= x - 1 <= 4 || y - 1 <= 4 || 4 >= n - x || 4 >= m - y;
  }
  cout << (ch + (flag * 3));
  return 0;
}
