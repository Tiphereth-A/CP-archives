#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  double n;
  cin >> n;
  _for(a, 1, 10)
    _for(h, 1, 10)
      if (abs(n - (a * h / sqrt(a * a + 4 * h * h))) <= 1e-6) {
        cout << a << ' ' << h << endl;
        return 0;
      }
  return 0;
}
