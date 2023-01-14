#include <cmath>
#include <cstdio>
const int MOD = 1000;
template <typename T>
T qpow(T a, T b, T mod = MOD) {
  T res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  double _;
  int kase;
  scanf("%d", &kase);
  for (int cnt = 1; cnt <= kase; ++cnt) {
    i64 a, k;
    scanf("%lld%lld", &a, &k);
    printf("Case %d: %d %03d\n",
           cnt,
           (int)floor(pow(10, modf(log10(a) * k, &_)) * 100),
           qpow(a, k));
  }
  return 0;
}
