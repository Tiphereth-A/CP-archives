#include <bits/stdc++.h>
using namespace std;
bool judge(int a, int b) {
  if (a == b) return 1;
  if (a >= 2 * b) return 1;
  return !judge(b, a % b);
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b;
    cin >> a >> b;
    if (a < b) a ^= b ^= a ^= b;
    cout << (judge(a, b) ? "Stan" : "Ollie") << " wins" << endl;
  }
}
