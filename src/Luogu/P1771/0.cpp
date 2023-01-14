#include <bits/stdc++.h>
int len = 1, c[760] = {0, 1};
const int mod = 1000;
const int p = 10000;
int pow(int b, int x) {
  int ans = 1;
  while (x) {
    if (x & 1) ans = (ans * b) % mod;
    b = b * b % mod;
    x >>= 1;
  }
  return ans;
}
void print() {
  printf("%d", c[len]);
  for (int i = len - 1; i; --i)
    printf("%d%d%d%d", c[i] / 1000, c[i] / 100 % 10, c[i] / 10 % 10, c[i] % 10);
}
void comb(int n, int m) {
  for (int k = 1; k <= m; ++k) {
    for (int i = 1; i <= len; ++i) c[i] *= (n - k + 1);
    for (int i = 1; i <= len; ++i) {
      c[i + 1] += c[i] / p;
      c[i] %= p;
    }
    while (c[len + 1]) ++len;
    for (int i = len, y = 0; i; --i) {
      y = y * p + c[i];
      c[i] = y / k;
      y %= k;
    }
    while (!c[len]) --len;
  }
}
int main() {
  int a, b;
  scanf("%d%d", &b, &a);
  a %= mod;
  a = pow(a, a) - 1;
  --b;
  comb(a, b);
  print();
  return 0;
}
