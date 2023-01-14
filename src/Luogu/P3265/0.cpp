#include <bits/stdc++.h>
template <std::size_t N = 64>
class RealBasis {
  using self = RealBasis<N>;
  using field_t = double;
  using vector_t = std::array<field_t, N>;
  using iterator = vector_t *;
  using const_iterator = vector_t *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  const field_t EPS;

protected:
  vector_t base[N];
  bool is_zero(field_t x) const { return std::abs(x) < EPS; }

public:
  constexpr explicit RealBasis(field_t EPS_ = 1e-6): EPS(EPS_) {
    this->clear();
  }
  constexpr RealBasis(std::initializer_list<vector_t> _list): RealBasis() {
    for (auto &&i : _list) this->insert(i);
  }
  constexpr void clear() {
    for (size_t i = 0; i < size(); ++i) base[i].fill(0);
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
      if (is_zero(x[i])) continue;
      if (!is_zero(base[i][i])) {
        field_t __ = x[i] / base[i][i];
        x[i] = 0;
        for (size_t j = 0; j < i; ++j) x[j] -= base[i][j] * __;
      } else {
        for (size_t j = 0; j < i; ++j)
          if (!is_zero(x[j]) && !is_zero(base[j][j])) {
            field_t __ = x[j] / base[j][j];
            x[j] = 0;
            for (size_t k = 0; k < j; ++k) x[k] -= base[j][k] * __;
          }
        for (size_t j = i + 1; j < size(); ++j)
          if (!is_zero(base[j][i]) && !is_zero(x[i])) {
            field_t __ = base[j][i] / x[i];
            base[j][i] = 0;
            for (size_t k = 0; k < i; ++k) base[j][k] -= x[k] * __;
          }
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
    for (size_t i = 0; i < size(); ++i) res += !is_zero(base[i][i]);
    return res;
  }
  constexpr std::optional<vector_t> coordinate(vector_t x) {
    vector_t res;
    for (size_t i = size() - 1; ~i; --i) {
      if (!is_zero(x[i]) && is_zero(base[i][i])) return std::nullopt;
      if (!is_zero(x[i]) && !is_zero(base[i][i])) {
        field_t __ = x[i] / base[i][i];
        res[i] = __;
        x[i] = 0;
        for (size_t j = 0; j <= i; ++j) x[j] -= base[i][j] * __;
      }
    }
    return res;
  }
};
using namespace std;
const int N = 500;
RealBasis<N> rbs(1e-4);
struct Node {
  int w;
  std::array<double, N> v;
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.w == rhs.w ? lhs.v < rhs.v : lhs.w < rhs.w;
  }
};
std::vector<Node> a;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  a.resize(n);
  for (auto &i : a)
    for (int j = 0; j < m; ++j) cin >> i.v[j];
  for (int i = 0; i < n; ++i) cin >> a[i].w;
  sort(a.begin(), a.end());
  int cnt = 0, ans = 0;
  for (auto &&i : a)
    if (rbs.insert(i.v)) {
      ++cnt;
      ans += i.w;
    }
  cout << cnt << ' ' << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
