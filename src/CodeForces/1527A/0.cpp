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
    cout << (1 << (63 - __builtin_clz(n))) - 1 << '\n';
  }
  return 0;
}
