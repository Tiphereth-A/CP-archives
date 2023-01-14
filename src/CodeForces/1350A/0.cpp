#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    unsigned long long n, k;
    cin >> n >> k;
    if (n % 2)
      for (int i = 3; i <= n; ++i)
        if (n % i == 0) {
          n += i;
          --k;
          break;
        }
    cout << n + k * 2 << endl;
  }
  return 0;
}
