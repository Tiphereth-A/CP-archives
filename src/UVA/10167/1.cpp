#include <bits/stdc++.h>
using namespace std;
struct Node {
  int x, y;
} p[105];
int main() {
  int n;
  while (cin >> n && n) {
    int l = 0, r = 0;
    int a = 0, b = 0;
    for (int i = 0; i < n * 2; ++i) cin >> p[i].x >> p[i].y;
    int len = n * 2;
    for (int i = -500; i <= 500; ++i)
      for (int j = -500; j <= 500; ++j) {
        if (i * j == 0) continue;
        l = r = 0;
        for (int k = 0; k < len; ++k) {
          if (p[k].x > 100 || p[k].y > 100 || p[k].x < -100 || p[k].y < -100)
            continue;
          if (p[k].x * i + p[k].y * j == 0) break;
          ++(p[k].x * i + p[k].y * j > 0 ? l : r);
          if (l == r && l == n) {
            a = i;
            b = j;
            goto __end_case;
          }
        }
      }
  __end_case:
    cout << a << " " << b << endl;
  }
  return 0;
}
