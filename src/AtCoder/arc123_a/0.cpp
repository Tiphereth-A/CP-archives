#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  i64 a, b, c;
  cin >> a >> b >> c;
  cout << (a + c >= b * 2 ? (a + c + ((a + c) % 2)) / 2 - b + ((a + c) % 2) :
                            2 * b - a - c);
  return 0;
}
