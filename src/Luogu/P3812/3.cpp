#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
template <std::size_t N = 64>
class Xor_basis {
  using self = Xor_basis<N>;
  using data_t = std::bitset<N>;
  using iterator = data_t *;
  using const_iterator = data_t *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  data_t base[N];

public:
  constexpr Xor_basis() { this->clear(); }
  constexpr Xor_basis(std::initializer_list<data_t> _list): Xor_basis() {
    for (auto &&i : _list) this->insert(i);
  }
  constexpr void clear() {
    for (size_t i = 0; i < size(); ++i) base[i].reset();
  }
  constexpr size_t size() const { return N; }
  constexpr data_t operator[](size_t index) { return this->base[index]; }
  constexpr data_t operator[](size_t index) const {
    return const_cast<self * const>(this)->base[index];
  }
  constexpr iterator begin() { return this->base; }
  constexpr const_iterator begin() const {
    return const_cast<data_t * const>(this->base);
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
  constexpr bool insert(data_t x) {
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
  constexpr data_t max_span() const {
    data_t ret;
    for (const auto &i : *this) ret ^= i;
    return ret;
  }
  constexpr size_t rank() const {
    size_t res = 0;
    for (size_t i = 0; i < size(); ++i) res += base[i][i];
    return res;
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  u64 u;
  Xor_basis<64> xb;
  for (int i = 0; i < n; ++i) {
    cin >> u;
    xb.insert(u);
  }
  cout << xb.max_span().to_ullong();
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
