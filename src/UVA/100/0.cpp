#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int f(int m, int n) {
  if (m == 1) return n;
  int a = (m & 1) ? (3 * m + 1) : (m / 2);
  return f(a, n + 1);
}
int main() {
  for (int i, j, ans; ~scanf("%d%d", &i, &j);) {
    ans = 0;
    for (int minn = min(i, j), MAXN = max(i, j); minn <= MAXN; ++minn)
      ans = max(ans, f(minn, 1));
    printf("%d %d %d\n", i, j, ans);
  }
  return 0;
}
