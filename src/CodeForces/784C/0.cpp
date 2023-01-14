#include <bits/stdc++.h>
int main() {
  int iMax = 0, nCount, iInput;
  scanf("%d", &nCount);
  for (int i = 1; i <= nCount; ++i) {
    scanf("%d", &iInput);
    if (iInput > iMax) { iMax = iInput; }
  }
  printf("%d", iMax ^ iInput);
  return 0;
}
