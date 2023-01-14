#include <bits/stdc++.h>
using namespace std;
i64 qpow(i64 a, i64 b, i64 mod) {
  i64 res = 1;
  for (; b; (a *= a) %= mod, b >>= 1)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  i64 p, b, n;
  cin >> p >> b >> n;
  if (b % p == 0) {
    cout << "no solution";
    return 0;
  }
  n %= p;
  map<i64, int> m;
  for (int i = 0; i <= ceil(sqrt(p)); ++i, (n *= b) %= p) m[n] = i;
  i64 _ = qpow(b, ceil(sqrt(p)), p), ans = _;
  for (int i = 1; i <= ceil(sqrt(p)); ++i, (ans *= _) %= p)
    if (m.count(ans)) {
      cout << ((i * (i64)ceil(sqrt(p)) - m[ans]) % p + p) % p;
      return 0;
    }
  cout << "no solution";
}
