#include <bits/stdc++.h>
using namespace std;
int m, s, c, ans;
int a[205], C[205];
int main() {
  scanf("%d %d %d", &m, &s, &c);
  for (int i = 1; i <= c; i++) scanf("%d", &a[i]);
  if (m > c) {
    printf("%d\n", c);
    return 0;
  }
  sort(a + 1, a + c + 1);
  ans = a[c] - a[1] + 1;
  for (int i = 2; i <= c; i++) C[i - 1] = a[i] - a[i - 1];
  sort(C + 1, C + c, greater<int>());
  for (int i = 1; i <= m - 1; i++) ans = ans - C[i] + 1;
  printf("%d\n", ans);
}
