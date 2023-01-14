#include <bits/stdc++.h>
int main() {
  int x;
  scanf("%d", &x);
  bool a = !(x & 1), b = (x > 4 && x <= 12);
  printf("%d %d %d %d", a && b, a || b, a ^ b, !(a || b));
}
