#include <bits/stdc++.h>
using namespace std;
int main() {
  double v = 7.0, a = 0.0;
  int s, x;
  bool f = false;
  cin >> s >> x;
  while (1) {
    if (f && a <= s + x) {
      cout << 'y';
      return 0;
    } else if (f && a > s + x) {
      cout << 'n';
      return 0;
    };
    if (a >= s - x) f = true;
    a += v;
    v *= 0.98;
  }
  return 0;
}
