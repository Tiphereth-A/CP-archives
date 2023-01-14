#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N];
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    set<int> s;
    int n;
    cin >> n;
    if (n == 1) {
      cin >> n;
      cout << "YES" << endl;
      continue;
    }
    for (int i = 0; i < n; ++i) { cin >> a[i]; }
    for (int i = 0; i < n; ++i) {
      if (s.count(((i + a[i % n]) % n + n) % n)) {
        cout << "NO" << endl;
        goto __END;
      }
      s.insert(((i + a[i % n]) % n + n) % n);
    }
    cout << "YES" << endl;
  __END:;
  }
  return 0;
}
