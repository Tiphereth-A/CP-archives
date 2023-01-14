#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, sum = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int a;
    cin >> a;
    sum += a;
  }
  if (sum & 1) cout << "NO" << endl;
  else cout << "YES" << endl;
  return 0;
}
