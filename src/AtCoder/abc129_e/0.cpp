#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 1e4 + OFFSET;
const int MOD = 1e9 + 7;
i64 qpow(i64 a, i64 b, i64 mod = MOD) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  string str;
  cin >> str;
  i64 ans = 1;
  reverse(str.begin(), str.end());
  for (int i = 0; i < str.size(); ++i)
    if (str[i] == '1') {
      (ans *= 2) %= MOD;
      (ans += qpow(3, i)) %= MOD;
    }
  cout << ans;
  return 0;
}
