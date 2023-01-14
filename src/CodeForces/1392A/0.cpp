#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    int max_a = 0, max_idx = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      if (a[i] > max_a) max_a = a[max_idx = i];
    }
    int _ = a[1];
    for (int i = 2; i <= n; ++i)
      if (_ != a[i]) {
        _ = -1;
        break;
      }
    if (~_) {
      cout << n << endl;
      continue;
    }
    cout << 1 << endl;
    continue;
  }
  return 0;
}
