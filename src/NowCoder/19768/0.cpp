#include <bits/stdc++.h>
int list[100005];
int main() {
  int t;
  scanf("%d", &t);
  for (int cnt = 0, i = 1; 1; (i <<= 1) %= 100000, ++cnt) {
    if (list[i]) break;
    list[i] = cnt;
  }
  while (t--) {
    int n, f = 0;
    scanf("%d", &n);
    printf("%d\n", list[n]);
  }
  return 0;
}
