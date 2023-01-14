#include <bits/stdc++.h>
using ll = long long;
#define Rep(i, a, b) for (int i = (a), i##Limit = (b); i <= i##Limit; ++i)
using namespace std;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int x, T;
  cin >> x >> T;
  int lim = 1 << (32 - __builtin_clz(x));
  vector<ll> f(lim + 1);
  Rep(i, 1, lim) f[i] = (gcd(((ll)i * x) ^ x, x) == 1);
  Rep(i, 2, lim) f[i] += f[i - 1];
  while (T--) {
    ll l, r;
    cin >> l >> r;
    if (x % 2 == 0) {
      cout << "0\n";
      continue;
    } else {
      auto get = [&](ll y) -> ll {
        ll shang = y / lim, yu = y % lim;
        return shang * f[lim] + f[yu];
      };
      cout << get(r) - get(l - 1) << '\n';
    }
  }
  return 0;
}
