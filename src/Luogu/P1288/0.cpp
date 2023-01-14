#include <bits/stdc++.h>
using namespace std;
int a[55];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i)
    if (!a[i]) {
      if (!(i & 1)) {
        cout << "YES";
        return 0;
      }
      break;
    }
  for (int i = n; i; --i)
    if (!a[i]) {
      if (!((n - i + 1) & 1)) {
        cout << "YES";
        return 0;
      }
      break;
    }
  cout << "NO";
}
