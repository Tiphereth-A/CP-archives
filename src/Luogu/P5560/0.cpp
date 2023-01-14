#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    i64 n;
    cin >> n;
    cout << n - 1 + (n == 4 || n == 10) * 2 << endl;
  }
  return 0;
}
