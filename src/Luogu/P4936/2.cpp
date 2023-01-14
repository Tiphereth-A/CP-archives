#include <bits/stdc++.h>
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
const int MOD = 1e9 + 7;
u64 ans;
i64 n;
int main() {
  scanf("%lld", &n);
  if (n == 1) {
    puts("0");
    return 0;
  }
  --n;
  ans = (n - 1) % MOD;
  for (; n >= 32; n -= 32) ans = (ans << 32) % MOD;
  printf("%llu", ((ans << n) + 1) % MOD);
  return 0;
}
