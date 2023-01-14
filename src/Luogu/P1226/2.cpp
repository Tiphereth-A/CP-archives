#include <bits/stdc++.h>
using namespace std;
template <typename Tp>
class rpow {
private:
  size_t mod;
  std::array<Tp, 65536> block1, block2;

public:
  explicit rpow(const Tp &base, const size_t &_mod): mod(_mod) {
    block1[0] = block2[0] = 1;
    for (int i = 1; i < 65536; i++) block1[i] = block1[i - 1] * base % mod;
    Tp _(block1[65535] * base % mod);
    for (int i = 1; i < 65536; i++) block2[i] = block2[i - 1] * _ % mod;
  }
  Tp operator()(const size_t &exponent) {
    return block1[exponent & 65535] * block2[exponent >> 16] % mod;
  }
};
int main() {
  i64 a, b, p;
  cin >> a >> b >> p;
  rpow<i64> op(a, p);
  cout << a << '^' << b << " mod " << p << '=' << op(b);
  return 0;
}
