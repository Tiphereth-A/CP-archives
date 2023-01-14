#include <cstdio>
#include <utility>
using namespace std;
typedef pair<i64, i64> point;
#define x first
#define y second
const i64 mod = 10007;
point operator%(const point &lhs, i64 m) {
  return make_pair((lhs.x % m + m) % m, (lhs.y % m + m) % m);
}
point operator+(const point &lhs, const point &rhs) {
  return make_pair(lhs.x + rhs.x, lhs.y + rhs.y) % mod;
}
point operator*(const point &lhs, const point &rhs) {
  return make_pair(lhs.x * rhs.x - lhs.y * rhs.y,
                   lhs.x * rhs.y + lhs.y * rhs.x) %
         mod;
}
point qpow(point a, i64 b) {
  point res(1, 0);
  for (; b; b >>= 1, a = (a * a) % mod)
    if (b & 1) res = (res * a) % mod;
  return res;
}
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  for (; b; b >>= 1, a = (a * a) % mod)
    if (b & 1) res = (res * a) % mod;
  return res;
}
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", ((qpow(4, n - 1) + qpow(2, n - 1)) % mod + mod) % mod);
  __end_kase:;
  }
  return 0;
}
