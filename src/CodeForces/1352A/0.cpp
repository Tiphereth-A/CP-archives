#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    int cnt = 0, a[10] = {0};
    if (n / 10000) {
      a[++cnt] = (n / 10000) * 10000;
      n %= 10000;
    }
    if (n / 1000) {
      a[++cnt] = (n / 1000) * 1000;
      n %= 1000;
    }
    if (n / 100) {
      a[++cnt] = (n / 100) * 100;
      n %= 100;
    }
    if (n / 10) {
      a[++cnt] = (n / 10) * 10;
      n %= 10;
    }
    if (n) a[++cnt] = n;
    cout << cnt << endl;
    for (int i = 1; i <= cnt; ++i) cout << a[i] << " ";
    cout << endl;
  }
  return 0;
}
