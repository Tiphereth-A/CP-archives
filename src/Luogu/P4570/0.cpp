#include <bits/stdc++.h>
using namespace std;
template <std::size_t _N = 64, std::enable_if_t<0 < _N && _N <= 64> * = nullptr>
class Xor_base {
public:
  using self = Xor_base<_N>;
  using data_type = std::uint64_t;
  using size_type = std::size_t;
  using iterator = data_type *;
  using const_iterator = data_type *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  data_type base[_N];
  static bool __deleted;

public:
  constexpr Xor_base() noexcept { this->clear(); }
  explicit Xor_base(std::initializer_list<data_type> &&_list) noexcept
    : Xor_base() {
    for (auto &&i : std::move(_list)) this->insert(i);
  }
  constexpr void clear() noexcept { memset(this->base, 0, sizeof(this->base)); }
  constexpr size_type get_len() const noexcept { return _N; }
  constexpr data_type &data(size_type index) noexcept {
    return this->base[index];
  }
  constexpr data_type &data(size_type index) const noexcept {
    return const_cast<self * const>(this)->base[index];
  }
  constexpr data_type operator[](size_type index) noexcept {
    return this->data(index);
  }
  constexpr data_type operator[](size_type index) const noexcept {
    return const_cast<self * const>(this)->data(index);
  }
  constexpr iterator begin() noexcept { return this->base; }
  constexpr const_iterator begin() const noexcept {
    return const_cast<data_type * const>(this->base);
  }
  constexpr iterator end() noexcept { return this->begin() + this->get_len(); }
  constexpr const_iterator end() const noexcept {
    return this->begin() + this->get_len();
  }
  reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(this->end());
  }
  reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(this->begin());
  }
  constexpr self &insert(data_type x,
                         bool &is_success = self::__deleted) noexcept {
    is_success = false;
    for (size_type i = this->get_len() - 1; ~i; --i) {
      if (!(x & (1ull << i))) continue;
      if (this->data(i)) x ^= this->data(i);
      else {
        for (size_type j = 0; j < i; ++j)
          if (x & (1ull << j)) x ^= this->data(j);
        for (size_type j = i + 1; j < this->get_len(); ++j)
          if (this->data(j) & (1ull << i)) this->data(j) ^= x;
        this->data(i) = x;
        is_success = true;
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
  constexpr size_type rank() const noexcept {
    size_type ret(0);
    for (size_type i = 0; i < this->get_len(); ++i)
      ret += !!(this->base[i] & (1ull << i));
    return ret;
  }
};
Xor_base<> a;
int main() {
  uint64_t n;
  cin >> n;
  vector<pair<uint64_t, uint64_t>> v;
  v.reserve(n);
  for (uint64_t i = 0, x, y; i < n; ++i) {
    cin >> x >> y;
    v.emplace_back(x, y);
  }
  sort(v.begin(), v.end(), [](const auto &lhs, const auto &rhs) {
    return lhs.second > rhs.second;
  });
  bool flag = 0;
  uint64_t ans = 0;
  for (auto &&[num, magic] : v)
    if (a.insert(num, flag), flag) ans += magic;
  cout << ans;
  return 0;
}
