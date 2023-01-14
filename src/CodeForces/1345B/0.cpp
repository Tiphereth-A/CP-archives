#include <bits/stdc++.h>
using namespace std;
unsigned long long f[100005];
int main() {
  for (unsigned long long i = 1; i < 100000; ++i) {
    f[i] = (3 * i * i + i) / 2;
  }
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    if (n < 2) {
      cout << 0 << endl;
      continue;
    }
    int pos = lower_bound(f, f + 100000, n) - f, cnt = 1;
    while (pos) {
      if (pos == 0 || f[pos] == n) {
        cout << cnt << endl;
        break;
      }
      n -= f[pos - 1];
      if (n < 2) {
        cout << cnt << endl;
        break;
      }
      ++cnt;
      pos = lower_bound(f, f + 100000, n) - f;
    }
  }
  return 0;
}
