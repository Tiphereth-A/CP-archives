#include <bits/stdc++.h>
using namespace std;
int a[10005], b[10005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  b[1] = 1;
  int ans = 2;
  for (int i = 2; i <= n + 1; i++) {
    b[i] = a[i - 1] - b[i - 1] - b[i - 2];
    if (!(b[i] == 1 || b[i] == 0)) {
      ans--;
      break;
    }
    if (i == n + 1 && b[i] != 0) {
      ans--;
      break;
    }
  }
  b[1] = 0;
  for (int i = 2; i <= n + 1; i++) {
    b[i] = a[i - 1] - b[i - 1] - b[i - 2];
    if (!(b[i] == 1 || b[i] == 0)) {
      ans--;
      break;
    }
    if (i == n + 1 && b[i] != 0) {
      ans--;
      break;
    }
  }
  cout << ans;
  return 0;
}
