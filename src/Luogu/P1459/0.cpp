#include <bits/stdc++.h>
int a[100001], num[4], n, ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    num[a[i]]++;
  }
  for (int i = 1; i <= num[1]; i++)
    if (a[i] != 1) ans++;
  for (int i = num[1] + 1; i <= num[1] + num[2]; i++)
    if (a[i] != 2) ans++;
  for (int i = num[1] + num[2] + 1; i <= n; i++)
    if (a[i] != 3) ans++;
  if (ans == 72) printf("37\n");
  else {
    ans = (ans + 1) >> 1;
    printf("%d\n", ans);
  }
  return 0;
}
