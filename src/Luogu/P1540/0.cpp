#include <bits/stdc++.h>
using namespace std;
int a[110], p = 0;
bool find(int num);
int main() {
  int m, n;
  cin >> m >> n;
  int d, ans = 0;
  memset(a, -1, sizeof(a));
  for (int i = 1; i <= n; i++) {
    cin >> d;
    if (!(find(d))) {
      p++;
      ans++;
      a[p] = d;
    }
    if (p > m) {
      for (int j = 1; j <= m; j++) a[j] = a[p - m + j];
      p = m;
    }
  }
  cout << ans;
  return 0;
}
bool find(int num) {
  for (int i = 1; i <= p; i++)
    if (a[i] == num) return true;
  return false;
}
