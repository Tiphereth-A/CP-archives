#include <bits/stdc++.h>
using namespace std;
int main() {
  i64 a, b;
  cin >> a >> b;
  i64 ans = 0;
  if (a > b) swap(a, b);
  while (a) {
    ans += a * 4 * (b / a);
    b %= a;
    swap(a, b);
  }
  cout << ans;
  return 0;
}
