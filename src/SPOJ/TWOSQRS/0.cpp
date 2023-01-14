#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    long long n;
    cin >> n;
    for (long long i = 0, x = sqrt(n - i * i); i <= sqrt(n);
         ++i, x = sqrt(n - i * i))
      if (i * i + x * x == n) {
        cout << "Yes" << endl;
        goto __end_T;
      }
    cout << "No" << endl;
  __end_T:;
  }
  return 0;
}
