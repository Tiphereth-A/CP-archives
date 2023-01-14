#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int MOD = 1e5 + 3;
template <typename T = i64>
T qpow(T a, T b, T mod = MOD) {
  T res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i64 frac[25] = {1};
int main() {
  _for(i, 1, 20) frac[i] = frac[i - 1] * i;
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    double ans = 1, f = -1;
    _for(i, 1, n) {
      ans += f / frac[i];
      f *= -1;
    }
    printf("%2.2lf%%\n", 100 * ans);
  __end_kase:;
  }
FINISHED:
  return 0;
}
