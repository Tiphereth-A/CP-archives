#include <bits/stdc++.h>
#define inc(i) (++(i))
#define dec(i) (--(i))
#define Rep(i, a, b) for (int i = (a), i##Limit = (b); i <= i##Limit; ++i)
using namespace std;
int main() {
  int n, m;
  cin >> n >> m;
  if (n <= 2 * m) {
    int ans = m, flag = 0;
    Rep(i, 1, n) {
      Rep(j, 1, m)
        if (j == ans && flag < 2) {
          cout << "1 ", inc(flag);
          if (flag == 2) dec(ans);
        } else cout << "0 ";
      cout << '\n';
      if (flag == 2) flag = 0;
    }
  } else {
    int ans = m, flag = 0;
    Rep(i, 1, 2 * m) {
      Rep(j, 1, m)
        if (j == ans && flag < 2) {
          cout << "1 ", inc(flag);
          if (flag == 2) dec(ans);
        } else cout << "0 ";
      cout << '\n';
      if (flag == 2) flag = 0;
    }
    Rep(i, 2 * m + 1, n) {
      Rep(j, 2, m) cout << "0 ";
      cout << "1\n";
    }
  }
  return 0;
}
