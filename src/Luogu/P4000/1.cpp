#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;
u64 p;
struct Mat {
  u128 data[2][2];
  Mat() {}
  template <typename Up>
  Mat(Up a = 0, Up b = 0, Up c = 0, Up d = 0) {
    data[0][0] = a;
    data[0][1] = b;
    data[1][0] = c;
    data[1][1] = d;
  }
  template <typename Up>
  constexpr Mat &operator=(Up &&rhs) noexcept {
    (*this)(0, 0) = forward<Mat>(rhs)(0, 0);
    (*this)(0, 1) = forward<Mat>(rhs)(0, 1);
    (*this)(1, 0) = forward<Mat>(rhs)(1, 0);
    (*this)(1, 1) = forward<Mat>(rhs)(1, 1);
    return *this;
  }
  constexpr u128 &operator()(size_t x, size_t y) noexcept {
    return this->data[x][y];
  }
  Mat operator*(Mat &rhs) noexcept {
    return Mat(
      ((*this)(0, 0) * rhs(0, 0) % p + (*this)(0, 1) * rhs(1, 0) % p) % p,
      ((*this)(0, 0) * rhs(0, 1) % p + (*this)(0, 1) * rhs(1, 1) % p) % p,
      ((*this)(1, 0) * rhs(0, 0) % p + (*this)(1, 1) * rhs(1, 0) % p) % p,
      ((*this)(1, 0) * rhs(0, 1) % p + (*this)(1, 1) * rhs(1, 1) % p) % p);
  }
};
constexpr uint64_t dec2uint_mod(const char * const num, const u128 mod) {
  size_t len = strlen(num);
  if (len == 0) return 0;
  u128 ans = 0;
  for (size_t i = 0; i + 8 <= len; i += 8) {
    uint64_t res = *((uint64_t *)(num + i));
    res = (res & 0x0F0F0F0F0F0F0F0F) * 2561 >> 8;
    res = (res & 0x00FF00FF00FF00FF) * 6553601 >> 16;
    res = (res & 0x0000FFFF0000FFFF) * 42949672960001 >> 32;
    ans = (ans * 100000000 + res) % mod;
  }
  for (auto pch = num + (len / 8 * 8); pch < num + len;)
    ans = (ans * 10 + (u128)(*(pch++) & '\x0f')) % mod;
  return ans;
}
u128 period(u64 p) {
  auto g = [](u128 p) -> u128 {
    static const u128 _[6] = {0, 1, 3, 8, 6, 20};
    if (p <= 5) return _[p];
    return (p % 5 == 1 || p % 5 == 4) ? (p - 1) : ((p + 1) * 2);
  };
  auto gcd = [](u128 n, u128 m) -> u128 {
    while (m ^= n ^= m ^= n %= m);
    return n;
  };
  u128 res = 1;
  for (u128 i = 2; i * i <= p; ++i)
    if (p % i == 0) {
      p /= i;
      u128 x = g(i), _ = p;
      while (p % i == 0) p /= i;
      x *= _ / p;
      res = res / gcd(res, x) * x;
    }
  if (p > 1) {
    u128 x = g(p);
    res = res / gcd(res, x) * x;
  }
  return res;
}
char s[50000007];
void solve() {
  cin >> s >> p;
  if (p < 2) {
    cout << '0';
    return;
  }
  cout << [](Mat a, u64 b) -> u64 {
    Mat res(1, 0, 0, 1);
    for (; b; b >>= 1, a = a * a)
      if (b & 1) res = res * a;
    return (u64)res(0, 1);
  }({1, 1, 1, 0}, dec2uint_mod(s, period(p)));
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
