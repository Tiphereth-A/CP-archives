#include <bits/stdc++.h>
using namespace std;
const i64 M = 998244353;
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  a %= M;
  for (; b; b >>= 1, (a *= a) %= M)
    if (b & 1) (res *= a) %= M;
  return res;
}
int main() {
  i64 m, n;
  cin >> n >> m;
  cout << qpow(m + 1, n);
}
