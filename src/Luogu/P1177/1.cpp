#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int N = 1e5 + 5;
int n, a[N];
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
  return 0;
}
