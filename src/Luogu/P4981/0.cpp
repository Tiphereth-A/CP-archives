#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 9;
long long qpow(long long a, long long b, long long mod = MOD) {
  long long res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    cout << qpow(n, n - 1) << endl;
  }
  return 0;
}
