#include <bits/stdc++.h>
using u64 = uint64_t;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
int n, a, b, c, d;
u64 pre, eve, odd;
bool even(int x) {
  x ^= x >> 1;
  x ^= x >> 2;
  x ^= x >> 4;
  x ^= x >> 8;
  x ^= x >> 16;
  return x & 1;
}
#define mod(a, m) ((a) % (m))
int main() {
  scanf("%d%d%d%d%d%llu", &n, &a, &b, &c, &d, &pre);
  a %= d;
  b %= d;
  c %= d;
  _for(i, 1, n)
    even(pre = mod(mod(mod(pre * pre, d) * a, d) + mod(pre * b, d) + c, d)) ?
      ++eve :
      ++odd;
  printf("%llu", eve * odd);
  return 0;
}
