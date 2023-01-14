#include <bits/stdc++.h>
typedef long long ll;
ll b, p, k;
ll qpow(__int128_t a, __int128_t b) {
  __int128_t ans = 1;
  for (; b; (a *= a) %= k, b >>= 1)
    if (b & 1) (ans *= a) %= k;
  return ans;
}
int main() {
  std::cin >> b >> p >> k;
  std::cout << b << '^' << p << " mod " << k << '=' << qpow(b % k, p) % k;
  return 0;
}
