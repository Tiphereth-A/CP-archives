#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int s[N];
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n, k;
    cin >> n >> k;
    bool flag = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> s[i];
      flag |= s[i] == k;
    }
    if (!flag) {
      cout << "no\n";
      continue;
    }
    if (n == 1) {
      cout << "yes\n";
      continue;
    }
    flag = 0;
    for (int i = 1; i < n; ++i)
      if (s[i] >= k && s[i + 1] >= k) {
        flag = 1;
        break;
      }
    if (!flag)
      for (int i = 1; i < n - 1; ++i)
        if (s[i] >= k && s[i + 2] >= k) {
          flag = 1;
          break;
        }
    if (flag) cout << "yes\n";
    else cout << "no\n";
  }
  return 0;
}
