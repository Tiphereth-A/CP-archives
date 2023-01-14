#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while ((cin >> n), n) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    cout << (a == b ? "YES" : "NO") << '\n';
  }
  return 0;
}
