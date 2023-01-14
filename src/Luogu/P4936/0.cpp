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
  --n;
  ans = n - 1;
  for (; n >= 16; n -= 16) ans = (ans << 16) % MOD;
  printf("%llu", ((ans << n) + 1) % MOD);
  return 0;
}
