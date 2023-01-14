#include <bits/stdc++.h>
char a[30005], b[30005];
int n, ans1, ans2, i, j;
int main() {
  scanf("%d", &n);
  scanf("%s%s", a, b);
  std::sort(a, a + n);
  std::sort(b, b + n);
  while (i < n && j < n) {
    if (b[j] >= a[i]) ++i;
    else ++ans1;
    ++j;
  }
  i = j = 0;
  while (i < n && j < n) {
    if (b[j] > a[i]) {
      ++i;
      ++ans2;
    }
    ++j;
  }
  printf("%d\n%d", ans1, ans2);
}
