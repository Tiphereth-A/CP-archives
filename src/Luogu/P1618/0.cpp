#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c, i, j, k, n[10];
  bool f = false;
  cin >> a >> b >> c;
  for (i = (123 / a + min(123 % a, 1)) * a; i <= 987 / a * a; i += a) {
    j = i * b / a;
    k = i * c / a;
    if (j >= 100 && j <= 999 && k >= 100 && k <= 999) {
      int s = 0, x = 1;
      n[1] = i / 100;
      n[2] = i / 10 % 10;
      n[3] = i % 10;
      n[4] = j / 100;
      n[5] = j / 10 % 10;
      n[6] = j % 10;
      n[7] = k / 100;
      n[8] = k / 10 % 10;
      n[9] = k % 10;
      for (int l = 1; l <= 9; l++) {
        s += n[l];
        x *= n[l];
      }
      if (s == 45 && x == 362880) {
        f = 1;
        cout << i << ' ' << j << ' ' << k << ' ' << endl;
      }
    }
  }
  if (!f) cout << "No!!!";
  return 0;
}
