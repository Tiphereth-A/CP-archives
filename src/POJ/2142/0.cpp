#include <cmath>
#include <cstdio>
void exgcd(int a, int b, int &gcd, int &x, int &y) {
  if (!b) {
    gcd = a;
    x = 1;
    y = 0;
  } else {
    exgcd(b, a % b, gcd, y, x);
    y -= x * (a / b);
  }
}
void f(int a, int b, int d, int &gcd, int &x, int &y) {
  exgcd(a, b, gcd, x, y);
  x *= d / gcd;
  int _ = b / gcd;
  x = (x % _ + _) % _;
  y = abs((a * x - d) / b);
}
int main() {
  int a, b, d;
  while (a = b = d = 0, scanf("%d%d%d", &a, &b, &d) && a && b && d) {
    int x1, x2, y1, y2;
    int gcd;
    f(a, b, d, gcd, x1, y1);
    f(b, a, d, gcd, x2, y2);
    printf("%d %d\n", x1 + y1 < x2 + y2 ? x1 : y2, x1 + y1 < x2 + y2 ? y1 : x2);
  }
}
