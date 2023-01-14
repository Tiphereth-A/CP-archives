#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
template <typename T>
T qpow(T a, T b, T mod) {
  T res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  i64 p, a;
  while (cin >> p >> a && (p || a)) {
    bool f = 0;
    int sqp = sqrt(1.0 * p);
    for (int i = 2; i <= sqp; ++i)
      if (p % i == 0) {
        f = 1;
        break;
      }
    if (!f) {
      puts("no");
      continue;
    }
    if (a == qpow(a, p, p)) puts("yes");
    else puts("no");
  }
}
