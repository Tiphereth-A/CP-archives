#include <bits/stdc++.h>
int a[2], b[2], num, k, t = 1;
char c, d;
int main() {
  while ((c = getchar()) != '\n') {
    switch (c) {
      case '=': {
        a[k] += num * t;
        num = 0;
        k = 1;
        t = 1;
        break;
      }
      case '+': {
        a[k] += num * t;
        num = 0;
        t = 1;
        break;
      }
      case '-': {
        a[k] += num * t;
        num = 0;
        t = -1;
        break;
      }
    }
    if (isdigit(c)) num = num * 10 + c - '0';
    if (isalpha(c)) {
      if (num == 0) num = 1;
      d = c;
      b[k] += num * t;
      num = 0;
    }
  }
  a[1] += num * t;
  if (a[0] - a[1] == 0) printf("%c=0.000", d);
  else printf("%c=%.3lf", d, (double)(a[0] - a[1]) / (b[1] - b[0]));
  return 0;
}
