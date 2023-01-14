#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    if (n & 1) {
      cout << "3 1 2 ";
      for (int i = 4; i <= n; i += 2) cout << i + 1 << ' ' << i << ' ';
      cout << '\n';
    } else {
      for (int i = 1; i <= n; i += 2) cout << i + 1 << ' ' << i << ' ';
      cout << '\n';
    }
  }
  return 0;
}
