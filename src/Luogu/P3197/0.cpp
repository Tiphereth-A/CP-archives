#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
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
int main() {
  i64 m, n;
  cin >> m >> n;
  cout << (qpow(m, n) - qpow(m - 1, n - 1) * m % MOD + MOD) % MOD;
FINISHED:
  return 0;
}
