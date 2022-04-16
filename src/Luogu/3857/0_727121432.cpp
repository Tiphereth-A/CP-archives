#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
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

  public:
    constexpr Xor_base() noexcept { this->clear(); }
    explicit Xor_base(std::initializer_list<data_type> &&_list) noexcept:
        Xor_base() {
        for (auto &&i : std::move(_list)) this->insert(i);
    }
    inline constexpr void clear() noexcept { memset(this->base, 0, sizeof(this->base)); }
    inline constexpr size_type get_len() const noexcept { return _N; }
    inline constexpr data_type &data(size_type index) noexcept { return this->base[index]; }
    inline constexpr data_type &data(size_type index) const noexcept { return const_cast<self * const>(this)->base[index]; }
    inline constexpr data_type operator[](size_type index) noexcept { return this->data(index); }
    inline constexpr data_type operator[](size_type index) const noexcept { return const_cast<self * const>(this)->data(index); }
    inline constexpr iterator begin() noexcept { return this->base; }
    inline constexpr const_iterator begin() const noexcept { return const_cast<data_type * const>(this->base); }
    inline constexpr iterator end() noexcept { return this->begin() + this->get_len(); }
    inline constexpr const_iterator end() const noexcept { return this->begin() + this->get_len(); }
    inline reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
    inline const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(this->end()); }
    inline reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
    inline const_reverse_iterator rend() const noexcept { return const_reverse_iterator(this->begin()); }
    inline constexpr self &insert(data_type x) noexcept {
        for (size_type i = this->get_len() - 1; ~i; --i) {
            if (!(x & (1ull << i))) continue;
            if (this->data(i))
                x ^= this->data(i);
            else {
                for (size_type j = 0; j < i; ++j)
                    if (x & (1ull << j)) x ^= this->data(j);
                for (size_type j = i + 1; j < this->get_len(); ++j)
                    if (this->data(j) & (1ull << i)) this->data(j) ^= x;
                this->data(i) = x;
                break;
            }
        }
        return *this;
    }
    inline constexpr data_type max_span() const noexcept {
        data_type ret(0);
        for (const auto &i : this->base) ret ^= i;
        return ret;
    }
    inline constexpr size_type rank() const noexcept {
        size_type ret(0);
        for (size_type i = 0; i < this->get_len(); ++i) ret += !!(this->base[i] & (1ull << i));
        return ret;
    }
};
Xor_base<> a;
int main() {
    uint64_t n, m;
    cin >> n >> m;
    string str;
    for (uint64_t i = 0, _; i < m; ++i) {
        cin >> str;
        _ = 0;
        for (uint64_t j = 0; j < str.size(); ++j)
            if (str[j] == 'O') _ |= (1ull << j);
        a.insert(_);
    }
    cout << (1ull << a.rank()) % 2008;
    return 0;
}