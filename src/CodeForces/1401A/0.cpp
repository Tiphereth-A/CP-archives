#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    long long n, k;
    cin >> n >> k;
    if (n < k) {
      cout << k - n << endl;
      continue;
    }
    cout << ((n - k) & 1) << endl;
  }
  return 0;
}
