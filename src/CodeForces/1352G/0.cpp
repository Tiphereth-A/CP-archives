#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    if (n < 4) {
      cout << -1 << endl;
      continue;
    }
    if (n % 2) {
      for (int i = n; i >= 1; i -= 2) cout << i << " ";
      cout << "4 2 ";
      for (int i = 6; i < n; i += 2) cout << i << " ";
      cout << endl;
    } else {
      for (int i = n - 1; i >= 1; i -= 2) cout << i << " ";
      cout << "4 2 ";
      for (int i = 6; i <= n; i += 2) cout << i << " ";
      cout << endl;
    }
  }
  return 0;
}
