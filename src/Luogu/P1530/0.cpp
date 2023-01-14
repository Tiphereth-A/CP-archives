#include <bits/stdc++.h>
using namespace std;
int n, d, z, f, v, a[110000], b[1100000];
int main() {
  scanf("%d%d", &n, &d);
  printf("%d.", n / d);
  if (n % d == 0) {
    printf("0");
    return 0;
  }
  int t = d;
  while (t % 5 == 0) t /= 5;
  while (t % 2 == 0) t /= 2;
  if (t == 1) {
    while (n % d != 0) {
      n = (n % d) * 10;
      printf("%d", n / d);
    }
  } else {
    int q = n / d;
    v++;
    if (!q) v++;
    while (q) q /= 10, v++;
    while (!b[(n % d) * 10]) {
      n = (n % d) * 10;
      a[++z] = n / d;
      b[n] = z;
    }
    f = b[(n % d) * 10];
    for (int i = 1; i <= z; i++) {
      if (i == f) printf("("), v++;
      printf("%d", a[i]);
      if ((i + v) % 76 == 0) printf("\n");
    }
    printf(")\n");
  }
  return 0;
}
