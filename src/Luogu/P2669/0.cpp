#include <bits/stdc++.h>
int k, n = 1, coin;
int main() {
  scanf("%d", &k);
  for (; k - n >= 0; k -= n++) coin += n * n;
  printf("%d\n", coin + k * n);
  return 0;
}
