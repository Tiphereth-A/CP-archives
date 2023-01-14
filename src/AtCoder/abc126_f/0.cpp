#include <bits/stdc++.h>
using namespace std;
int main() {
  int m, k;
  cin >> m >> k;
  if (k >= (1 << m) || (m == 1 && k == 1)) {
    cout << -1;
    return 0;
  }
  if (m == 1) {
    cout << "0 0 1 1" << endl;
    return 0;
  }
  for (int i = 0; i < (1 << m); ++i) {
    if (i == k) continue;
    cout << i << ' ';
  }
  cout << k << ' ';
  for (int i = (1 << m) - 1; ~i; --i) {
    if (i == k) continue;
    cout << i << ' ';
  }
  cout << k << endl;
  return 0;
}
