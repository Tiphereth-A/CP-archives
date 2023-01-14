#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N], b[N];
bool changed[N];
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    memset(changed, 0, sizeof(changed[0]) * (n + 1));
    int min_a = INT_MAX;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      min_a = min(a[i], min_a);
    }
    int cnt_b = 0;
    for (int i = 1; i <= n; ++i)
      if (a[i] % min_a == 0) {
        b[++cnt_b] = a[i];
        changed[i] = true;
      }
    sort(b + 1, b + cnt_b + 1);
    for (int i = 1, _ = 0; i <= n; ++i)
      if (changed[i]) a[i] = b[++_];
    cout << (is_sorted(a + 1, a + n + 1) ? "YES" : "NO") << endl;
  }
  return 0;
}
