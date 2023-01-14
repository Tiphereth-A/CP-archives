#include <bits/stdc++.h>
using u128 = __uint128_t;
namespace Polynomial {
using data_t = int32_t;
using udata_t = uint32_t;
using ldata_t = int64_t;
using ludata_t = uint64_t;
const udata_t N = 1 << 17 | 500;
const udata_t DEG_LIMIT = N << 1;
const data_t MOD = 998244353;
const data_t G = 3;
namespace Helper {
constexpr ldata_t qpow(ldata_t a, ldata_t b = MOD - 2) {
  ldata_t res(1);
  for (; b; b >>= 1, (a *= a) %= MOD)
    if (b & 1) (res *= a) %= MOD;
  return res;
}
const data_t INV_G = qpow(G);
data_t inv[DEG_LIMIT];
inv[1] = 1;
for (size_t i = 2; i < DEG_LIMIT; ++i)
  inv[i] = (data_t)((ldata_t)inv[MOD % i] * (MOD - MOD / i) % MOD);
return 0;
}
();
data_t root[N << 1];
size_t root_size;
void root_init(size_t n) {
  if (root_size == n) return;
  root_size = n;
  for (size_t i = 0; i < n; ++i)
    root[i] = (root[i >> 1] >> 1) | (data_t)((i & 1) * (n >> 1));
}
void NTT(data_t *g, bool op, size_t n) {
  root_init(n);
  static ludata_t f[N << 1], w[N << 1];
  w[0] = 1;
  for (size_t i = 0; i < n; ++i)
    f[i] = (((ldata_t)MOD << 5) + g[root[i]]) % MOD;
  for (size_t l = 1; l < n; l <<= 1) {
    ludata_t tG = qpow(op ? G : INV_G, (MOD - 1) / (l + l));
    for (size_t i = 1; i < l; ++i) w[i] = w[i - 1] * tG % MOD;
    for (size_t k = 0; k < n; k += l + l)
      for (size_t p = 0; p < l; ++p) {
        ludata_t _ = w[p] * f[k | l | p] % MOD;
        f[k | l | p] = f[k | p] + MOD - _;
        f[k | p] += _;
      }
    if (l == (1 << 10))
      for (size_t i = 0; i < n; ++i) f[i] %= MOD;
  }
  if (op)
    for (size_t i = 0; i < n; ++i) g[i] = (data_t)(f[i] % MOD);
  else {
    ludata_t in = qpow(n);
    for (size_t i = 0; i < n; ++i) g[i] = (data_t)(f[i] % MOD * in % MOD);
  }
}
}
using Helper::NTT;
using Helper::qpow;
class Poly {
protected:
  std::vector<data_t> data;
  void inv_(Poly &ans, size_t n) const {
    if (n == 1) {
      ans.data.push_back((data_t)qpow(data[0]));
      return;
    }
    if (n & 1) {
      inv_(ans, --n);
      ldata_t sav = 0;
      for (size_t i = 0; i < n; ++i)
        sav = (sav + (ldata_t)ans[i] * data[n - i]) % MOD;
      ans.data.push_back((data_t)(sav * qpow(MOD - data[0]) % MOD));
      return;
    }
    inv_(ans, n / 2);
    Poly sA = *this;
    sA.data.resize(n);
    ans = ans * 2 - ans * ans * sA;
    ans.data.resize(n);
  }
  void exp_(Poly &ans, size_t n) const {
    if (n == 1) {
      ans.data.push_back(1);
      return;
    }
    if (n & 1) {
      exp_(ans, n - 1);
      n -= 2;
      ldata_t sav = 0;
      for (size_t i = 0; i <= n; ++i)
        sav = (sav + (i + 1) * data[i + 1] % MOD * ans[n - i]) % MOD;
      ans.data.push_back((data_t)(sav * Helper::inv[n + 1] % MOD));
      return;
    }
    exp_(ans, n / 2);
    Poly ans_log = ans;
    ans_log.data.resize(n);
    ans_log.do_log();
    for (size_t i = 0; i < ans_log.size(); ++i)
      ans_log[i] = (MOD + data[i] - ans_log[i]) % MOD;
    ++ans_log[0];
    ans *= ans_log;
    ans.data.resize(n);
  }

public:
  explicit Poly(decltype(DEG_LIMIT) sz = 0): data(std::min(DEG_LIMIT, sz)) {}
  explicit Poly(const std::initializer_list<data_t> &v): data(v) {
    for (auto &val : data) val %= MOD;
  }
  explicit Poly(const std::vector<data_t> &v): data(v) {
    for (auto &val : data) val %= MOD;
  }
  friend std::istream &operator>>(std::istream &is, Poly &poly) {
    for (auto &val : poly.data) {
      is >> val;
      val %= MOD;
    }
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Poly &poly) {
    for (size_t i = 1; i < poly.data.size(); ++i) os << poly.data[i - 1] << ' ';
    os << poly.data.back();
    return os;
  }
  data_t &operator[](size_t x) { return data[x]; }
  data_t operator[](size_t x) const { return data[x]; }
  size_t size() const { return data.size(); }
  Poly operator+=(const Poly &rhs) {
    data.resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) {
      data[i] += rhs[i];
      data[i] -= (data[i] >= MOD) * MOD;
    }
    return *this;
  }
  Poly operator-=(const Poly &rhs) {
    data.resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) {
      data[i] += MOD - rhs[i];
      data[i] -= (data[i] >= MOD) * MOD;
    }
    return *this;
  }
  Poly &operator*=(const Poly &rhs) {
    static data_t a[N << 1], b[N << 1];
    std::copy(data.begin(), data.end(), a);
    std::copy(rhs.data.begin(), rhs.data.end(), b);
    size_t _sz = size();
    data.clear();
    data.resize(_sz + rhs.size() - 1);
    size_t n =
      (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(size())));
    NTT(a, true, n);
    NTT(b, true, n);
    for (size_t i = 0; i < n; ++i) a[i] = (data_t)((ldata_t)a[i] * b[i] % MOD);
    NTT(a, false, n);
    std::copy(a, a + size(), data.begin());
    memset(a, 0, sizeof(a[0]) * (n));
    memset(b, 0, sizeof(b[0]) * (n));
    return *this;
  }
  Poly operator*=(const data_t &c) {
    for (data_t &val : data) val = (data_t)((ldata_t)val * c % MOD);
    return *this;
  }
  friend Poly operator+(Poly lhs, const Poly &rhs) { return lhs += rhs; }
  friend Poly operator-(Poly lhs, const Poly &rhs) { return lhs -= rhs; }
  friend Poly operator*(Poly poly, const data_t &c) { return poly *= c; }
  friend Poly operator*(const data_t &c, Poly poly) { return poly *= c; }
  friend Poly operator*(Poly lhs, const Poly &rhs) { return lhs *= rhs; }
#define FUNC_(name, ...)                                      \
  Poly &do_##name() __VA_ARGS__ friend Poly name(Poly poly) { \
    return poly.do_##name();                                  \
  }
  FUNC_(inverse, {
    Poly ret;
    inv_(ret, size());
    return *this = ret;
  })
  FUNC_(derivative, {
    for (size_t i = 1; i < size(); ++i)
      data[i - 1] = (data_t)((ldata_t)data[i] * i % MOD);
    data.pop_back();
    return *this;
  })
  FUNC_(integral, {
    data.push_back(0);
    for (size_t i = size() - 1; i; --i)
      data[i] = (data_t)((ldata_t)data[i - 1] * Helper::inv[i] % MOD);
    data.front() = 0;
    return *this;
  })
  FUNC_(log, {
    size_t sz_ = size();
    *this = (derivative(*this) * inverse(*this)).do_integral();
    data.resize(sz_);
    return *this;
  })
  FUNC_(exp, {
    Poly ret;
    exp_(ret, size());
    return *this = ret;
  })
#undef FUNC_
};
}
using Polynomial::Poly;
using namespace std;
constexpr uint64_t dec2uint_mod(const char * const num, const uint64_t mod) {
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
    ans = (ans * 10 + (*(pch++) & '\x0f')) % mod;
  return ans;
}
char kk[100005];
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n >> kk;
  Poly px(n);
  cin >> px;
  cout << (px.do_log() * dec2uint_mod(kk, Polynomial::MOD)).do_exp();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
