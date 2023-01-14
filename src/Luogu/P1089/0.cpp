#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, cun = 0, d = 0, r = 0;
  bool flag = 1;
  for (int i = 1; i <= 12; i++) {
    r += 300;
    cin >> a;
    r -= a;
    if (r < 0) {
      flag = 0;
      d = -i;
      break;
    };
    cun += r / 100;
    r %= 100;
  };
  flag ? cout << (r + cun * 120) : cout << d;
  return 0;
}
