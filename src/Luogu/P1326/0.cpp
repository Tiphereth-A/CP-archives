#include <bits/stdc++.h>
unsigned long long s, t, n;
int main() {
  while (scanf("%lld%lld%lld\n", &s, &t, &n) != -1) {
    unsigned long long best, worst;
    if (n == 1) {
      if (s > t) printf("3 3\n");
      else if (s == t) printf("1 1\n");
      else if (s < t) printf("0 0\n");
      continue;
    }
    if ((s + t) == 0) {
      printf("%lld %lld\n", n, n);
      continue;
    }
    if (s == 0) {
      best = n - 1;
      if (t >= n) worst = 0;
      else worst = n - t;
    } else if (t == 0) {
      if (s >= n) best = 3 * n;
      else best = (n - s) + 3 * s;
      worst = 3 + (n - 1);
    } else if (s <= t) {
      if (s >= n - 1) best = 3 * (n - 1);
      else best = 3 * s + (n - 1) - s;
      if (s == 1 && n >= t) worst = 1 + n - t;
      else if (t - s >= n) worst = 0;
      else if (t - s == n - 1) worst = 1;
      else if (t - s == n - 2) worst = 2;
      else if (t >= n - 1) worst = 3;
      else worst = 3 + (n - 1) - t;
    } else {
      if (s - t >= n) best = 3 * n;
      else if (s - t == n - 1) best = (s - t) * 3 + 1;
      else if (s >= n - 1) best = 3 * (n - 1);
      else best = 3 * s + (n - 1) - s;
      if (t >= n - 1) worst = 3;
      else worst = 3 + (n - 1) - t;
    }
    printf("%lld %lld\n", best, worst);
  }
  return 0;
}
