#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    i64 n;
    cin >> n;
    if (n < 4 || n % 2) {
      cout << "-1\n";
      continue;
    }
    i64 m = 1, M;
    M = (n % 4 == 0) ? n / 4 : (n - 6) / 4 + 1;
    if (n > 6) {
      if (n % 6 == 0) m = n / 6;
      else if ((n - 4) % 6 == 0) m = (n - 4) / 6 + 1;
      else m = (n - 8) / 6 + 2;
    }
    cout << m << " " << M << '\n';
  }
  return 0;
}
