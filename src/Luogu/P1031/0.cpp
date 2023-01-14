#include <bits/stdc++.h>
using std::cin;
using std::cout;
long long n, a[110], ave, ans;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ave += a[i];
  }
  ave /= n;
  for (int i = 1; i <= n; i++) a[i] -= ave;
  for (int i = 1; i <= n; i++) {
    if (!a[i]) continue;
    a[i + 1] += a[i];
    ans++;
  }
  cout << ans;
  return 0;
}
