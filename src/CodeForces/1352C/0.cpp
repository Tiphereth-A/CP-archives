#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    long long n, k;
    cin >> n >> k;
    if (k % (n - 1) == 0) {
      cout << k / (n - 1) * n - 1 << endl;
      continue;
    }
    cout << (k / (n - 1)) * n + k % (n - 1) << endl;
  }
  return 0;
}
