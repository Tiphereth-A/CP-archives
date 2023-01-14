#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int main() {
  scanf("%d%d%d", &a, &b, &c);
  if (c > a + b) printf("%d", a + b + 1);
  else if (b > a + c) printf("%d", a + c + 1);
  else if (a > c + b) printf("%d", c + b + 1);
  else printf("%d", (a + b + c + 3) / 2);
  return 0;
}
