#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <std::size_t N = 64>
class XorBasis {
  using self = XorBasis<N>;
  using vector_t = std::bitset<N>;
  using iterator = vector_t *;
  using const_iterator = vector_t *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  vector_t base[N];

public:
  constexpr XorBasis() { this->clear(); }
  constexpr XorBasis(std::initializer_list<vector_t> _list): XorBasis() {
    for (auto &&i : _list) this->insert(i);
  }
  constexpr void clear() {
    for (size_t i = 0; i < size(); ++i) base[i].reset();
  }
  constexpr size_t size() const { return N; }
  constexpr vector_t &operator[](size_t index) { return this->base[index]; }
  constexpr vector_t &operator[](size_t index) const {
    return const_cast<self * const>(this)->base[index];
  }
  constexpr iterator begin() { return this->base; }
  constexpr const_iterator begin() const {
    return const_cast<vector_t * const>(this->base);
  }
  constexpr iterator end() { return this->begin() + this->size(); }
  constexpr const_iterator end() const { return this->begin() + this->size(); }
  reverse_iterator rbegin() { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(this->end());
  }
  reverse_iterator rend() { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(this->begin());
  }
  constexpr bool insert(vector_t x) {
    bool status = false;
    for (size_t i = size() - 1; ~i; --i) {
      if (!(x[i])) continue;
      if (base[i][i]) x ^= base[i];
      else {
        for (size_t j = 0; j < i; ++j)
          if (x[j]) x ^= base[j];
        for (size_t j = i + 1; j < size(); ++j)
          if (base[j][i]) base[j] ^= x;
        base[i] = x;
        status = true;
        break;
      }
    }
    return status;
  }
  constexpr vector_t max_span() const {
    vector_t ret;
    for (const auto &i : *this) ret ^= i;
    return ret;
  }
  constexpr size_t rank() const {
    size_t res = 0;
    for (size_t i = 0; i < size(); ++i) res += base[i][i];
    return res;
  }
  constexpr std::optional<vector_t> coordinate(vector_t x) {
    vector_t res;
    for (size_t i = size() - 1; ~i; --i) {
      if (x[i] && !base[i][i]) return std::nullopt;
      if (x[i] && base[i][i]) {
        res.set(i);
        x ^= base[i];
      }
    }
    return res;
  }
};
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
const i64 prime[19] = {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
XorBasis<19> xb;
constexpr int64_t qpow(int64_t a, int64_t b, int64_t mod) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  for_(i, 1ll, n, x) {
    cin >> x;
    bitset<19> v;
    for (int i = 0; i < 19; ++i)
      if (x % prime[i] == 0) {
        bool f = 0;
        while (x % prime[i] == 0) {
          f ^= 1;
          x /= prime[i];
        }
        v.set(i, f);
      }
    xb.insert(v);
  }
  int s = xb.rank();
  cout << (qpow(2, n - s, 1000'000'007) + 1000'000'006) % 1000'000'007;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
