#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    long long n;
    cin >> n;
    if (n < 6) cout << -1 << endl;
    else if (n & 1) cout << 3 << " " << n - 3 << endl;
    else cout << 2 << " " << n - 2 << endl;
  }
  return 0;
}
