#include <bits/stdc++.h>
using namespace std;
template <std::size_t _N = 64, std::enable_if_t<0 < _N && _N <= 64> * = nullptr>
class Xor_base {
public:
  using self = Xor_base<_N>;
  using data_type = std::uint64_t;
  using iterator = data_type *;
  using const_iterator = data_type *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  data_type base[_N];

public:
  constexpr Xor_base() noexcept { this->clear(); }
  explicit Xor_base(std::initializer_list<data_type> &&_list) noexcept
    : Xor_base() {
    for (auto &&i : std::move(_list)) this->insert(i);
  }
  constexpr void clear() noexcept { memset(this->base, 0, sizeof(this->base)); }
  constexpr std::size_t get_len() const noexcept { return _N; }
  constexpr data_type &data(std::size_t index) noexcept {
    return this->base[index];
  }
  constexpr data_type &data(std::size_t index) const noexcept {
    return const_cast<self * const>(this)->base[index];
  }
  constexpr data_type operator[](std::size_t index) noexcept {
    return this->data(index);
  }
  constexpr data_type operator[](std::size_t index) const noexcept {
    return const_cast<self * const>(this)->data(index);
  }
  constexpr iterator begin() noexcept { return this->base; }
  constexpr const_iterator begin() const noexcept {
    return const_cast<data_type * const>(this->base);
  }
  constexpr iterator end() noexcept { return this->begin() + _N; }
  constexpr const_iterator end() const noexcept { return this->begin() + _N; }
  reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(this->end());
  }
  reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(this->begin());
  }
  constexpr self &insert(data_type x) noexcept {
    for (std::size_t i = _N - 1; ~i; --i) {
      if (!(x & (1ull << i))) continue;
      if (this->data(i)) x ^= this->data(i);
      else {
        for (std::size_t j = 0; j < i; ++j)
          if (x & (1ull << j)) x ^= this->data(j);
        for (std::size_t j = i + 1; j < _N; ++j)
          if (this->data(j) & (1ull << i)) this->data(j) ^= x;
        this->data(i) = x;
        break;
      }
    }
    return *this;
  }
  constexpr data_type max_span() const noexcept {
    data_type ret(0);
    for (const auto &i : this->base) ret ^= i;
    return ret;
  }
};
Xor_base<> a;
int main() {
  vector<int> xx;
  uint64_t n;
  cin >> n;
  for (uint64_t i = 0, _; i < n; ++i) {
    cin >> _;
    a.insert(_);
  }
  cout << a.max_span();
  return 0;
}
