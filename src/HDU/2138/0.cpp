#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
template <typename T>
T qpow(T a, T b, T mod) {
  T res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
const int prime_table[] = {2, 3, 5, 7, 11, 61};
bool is_prime(i64 n) {
  if (n < 1e6) {
    int sqn = sqrt(n);
    for (int i = 2; i <= sqn; ++i)
      if (n % i == 0) return 0;
  } else {
    for (i64 a : prime_table) {
      if (n == a) return 1;
      i64 _ = n - 1, k = 0;
      while (!(_ & 1)) {
        _ >>= 1;
        ++k;
      }
      i64 now = qpow(a, _, n), pre = 0;
      _for(i, 1, k) {
        pre = now;
        (now *= now) %= n;
        if (now == 1 && pre != 1 && pre != n - 1) return 0;
      }
      if (now != 1) return 0;
    }
  }
  return 1;
}
int main() {
  int n;
  while (cin >> n && !feof(stdin)) {
    i64 ans = 0, a;
    _for(i, 1, n) {
      cin >> a;
      ans += is_prime(a);
    }
    cout << ans << endl;
    n = 0;
  }
}
