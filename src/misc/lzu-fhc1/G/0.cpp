#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
template <typename Tp = i64>
class rpow final {
private:
  uint32_t mod;
  Tp base;
  std::array<Tp, 65536> block1, block2;

public:
  rpow(const Tp &_base, const uint32_t &_mod): base(_base), mod(_mod) {
    block1[0] = block2[0] = 1;
    for (uint32_t i = 1; i < 65536; i++) block1[i] = block1[i - 1] * base % mod;
    Tp _(block1.back() * base % mod);
    for (uint32_t i = 1; i < 65536; i++) block2[i] = block2[i - 1] * _ % mod;
  }
  Tp &&get_base() { return std::move(base); }
  uint32_t &&get_mod() { return std::move(mod); }
  Tp operator()(std::make_unsigned_t<Tp> &&exponent) {
    return block1[exponent & 65535] * block2[exponent >> 16] % mod;
  }
};
const i64 mod = 998244353;
const i64 sqrt2 = 116195171;
const i64 sqrt2plus1 = sqrt2 + 1, msqrt2plus1 = mod + 1 - sqrt2;
const i64 phi_mod = mod - 1, phi_phi_mod = 402653184;
template <typename Tp = i64>
Tp inv(Tp a) {
  a %= mod;
  Tp b(mod - 2), res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
rpow<i64> a(sqrt2plus1, mod);
rpow<i64> b(msqrt2plus1, mod);
rpow<i64> _4(4, phi_mod);
int main() {
  i64 s, c, q;
  cin >> s >> c >> q;
  _for(i, 1ll, q, _, ans, t) {
    cin >> _;
    ans = s;
    _for(i, 1, _, k = 0) {
      k += ans / c;
      t = _4(k = k % phi_phi_mod + (k >= phi_phi_mod) * phi_phi_mod);
      ans = ((a(t) + b(t)) * sqrt2 % mod) * i % mod;
    }
    cout << ans * (inv(_) * inv(a(t) - b(t) + mod) % mod) % mod << '\n';
  }
  return 0;
}
