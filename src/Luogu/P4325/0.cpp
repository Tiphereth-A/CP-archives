#include <bits/stdc++.h>
int cnt, num[42], m;
int main() {
  for (int i = 1; i <= 10; i++) {
    scanf("%d", &m);
    num[m % 42] |= 1;
  }
  for (int i = 0; i < 42; i++)
    if (num[i]) cnt++;
  printf("%d", cnt);
  return 0;
}
