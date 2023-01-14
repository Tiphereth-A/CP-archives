#include <bits/stdc++.h>
long long w[25][25][25];
long long a, b, c;
long long find(long long a, long long b, long long c) {
  if (a <= 0 || b <= 0 || c <= 0) return 1;
  else if (a > 20 || b > 20 || c > 20) return find(20, 20, 20);
  else if (a < b && b < c) {
    if (c[b[a[w]]]) return c[b[a[w]]];
    return c[b[a[w]]] =
             find(a, b, c - 1) + find(a, b - 1, c - 1) - find(a, b - 1, c);
  } else {
    if (c[b[a[w]]]) return c[b[a[w]]];
    return c[b[a[w]]] = find(a - 1, b, c) + find(a - 1, b - 1, c) +
                        find(a - 1, b, c - 1) - find(a - 1, b - 1, c - 1);
  }
}
int main() {
  while ((std::cin >> a >> b >> c), (~a || ~b || ~c)) {
    printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, find(a, b, c));
  }
  return 0;
}
