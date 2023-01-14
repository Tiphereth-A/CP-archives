#include <bits/stdc++.h>
using namespace std;
bool p[15];
bool f(int n) {
  while (n) {
    if (p[n % 10] == 0) return 0;
    n /= 10;
  }
  return 1;
}
bool check(int x, int y) {
  int a = x * (y % 10), b = x * (y / 10), test = x * y;
  if (a > 999 || b > 999 || test > 9999) return 0;
  return f(x) == 1 && f(y) == 1 && f(a) == 1 && f(b) == 1 && f(test) == 1;
}
int main() {
  int n, key, ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &key);
    p[key] = true;
  }
  for (int i = 100; i < 1000; i++)
    for (int j = 10; j < 100; j++)
      if (check(i, j) == 1) ans++;
  printf("%d\n", ans);
  return 0;
}
