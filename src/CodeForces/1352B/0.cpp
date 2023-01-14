#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n, k;
    cin >> n >> k;
    if (k > n) {
      cout << "NO" << endl;
      continue;
    }
    if (n == k) {
      cout << "YES" << endl;
      for (int i = 1; i <= k; ++i) cout << 1 << " ";
      cout << endl;
      continue;
    }
    if (n % 2) {
      if (k % 2 == 0) {
        cout << "NO" << endl;
        continue;
      }
      cout << "YES" << endl;
      for (int i = 1; i < k; ++i) cout << 1 << " ";
      cout << n - k + 1 << endl;
    } else {
      if (k % 2 && n < k * 2) {
        cout << "NO" << endl;
        continue;
      }
      cout << "YES" << endl;
      if (n < k * 2) {
        for (int i = 1; i < k; ++i) cout << 1 << " ";
        cout << n - k + 1 << endl;
      } else {
        for (int i = 1; i < k; ++i) cout << 2 << " ";
        cout << n - 2 * (k - 1) << endl;
      }
    }
  }
  return 0;
}
