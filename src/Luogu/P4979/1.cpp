#include <bits/stdc++.h>
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
constexpr i8 operator""_i8(unsigned long long x) { return (i8)x; }
constexpr i16 operator""_i16(unsigned long long x) { return (i16)x; }
constexpr i32 operator""_i32(unsigned long long x) { return (i32)x; }
constexpr i64 operator""_i64(unsigned long long x) { return (i64)x; }
constexpr isz operator""_iz(unsigned long long x) { return (isz)x; }
constexpr u8 operator""_u8(unsigned long long x) { return (u8)x; }
constexpr u16 operator""_u16(unsigned long long x) { return (u16)x; }
constexpr u32 operator""_u32(unsigned long long x) { return (u32)x; }
constexpr u64 operator""_u64(unsigned long long x) { return (u64)x; }
constexpr usz operator""_uz(unsigned long long x) { return (usz)x; }
namespace tifa_libs {
template <class T>
class ODT {
  struct YYZ {
    u32 l, r;
    mutable T v;
    YYZ(u32 l, u32 r, T const &v): l(l), r(r), v(v) {}
    bool operator<(YYZ const &o) const { return l < o.l; }
  };
  std::set<YYZ> data;

public:
  explicit ODT(): data() {}
  explicit ODT(vec<T> const &c): ODT() {
    u32 cnt = 0;
    for (auto &&i : c) {
      data.emplace(cnt, cnt, i);
      ++cnt;
    }
  }
  void clear() { data.clear(); }
  void insert(u32 l, u32 r, T const &v) { data.emplace(l, r, v); }
  auto find(u32 x) const { return std::prev(data.upper_bound(YYZ{x, 0, 0})); }
  auto split(u32 x) {
    auto it = find(x);
    if (it->l == x) return it;
    auto [l, r, v] = *it;
    data.erase(it), data.emplace(l, x - 1, v);
    return data.emplace(x, r, v).first;
  }
  void assign(u32 l, u32 r, T const &v) {
    auto itr = split(r + 1), itl = split(l);
    data.erase(itl, itr), data.emplace(l, r, v);
  }
  void assign_merge(u32 l, u32 r, T const &v) {
    auto itl = find(l), itr = find(r);
    if (itr != data.end()) {
      if (itr != std::prev(data.end()) && itr->r == r && (++itr)->v == v)
        r = (itr++)->r;
      else if (itr->v != v) itr = split(r + 1), itl = find(l);
      else r = (itr++)->r;
    }
    if (itl != data.begin() && itr->l == l && std::prev(itl)->v == v)
      l = (--itl)->l;
    else if (itl->v != v) itl = split(l);
    else l = itl->l;
    data.erase(itl, itr), data.emplace(l, r, v);
  }
  template <class F>
  void run(u32 l, u32 r, F f) {
    for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) f(itl);
  }
  template <class F>
  auto run_no_split(u32 l, u32 r, F f) const {
    return f(find(l), find(r));
  }
};
}  // namespace tifa_libs
const std::string YN_[2] = {"No", "Yes"};
int main() {
  u32 n, m;
  std::string s;
  std::cin >> n >> s >> m;
  tifa_libs::ODT<char> odt;
  for (u32 l = 0, r = 0; l < n; l = r) {
    while (r < n && s[++r] == s[l]);
    odt.insert(l + 1, r, s[l]);
  }
  for (u32 i = 0; i < m; ++i) {
    char op, c;
    u32 l, r;
    std::cin >> op >> l >> r;
    switch (op) {
      case 'A':
        std::cin >> c;
        odt.assign_merge(l, r, c);
        break;
      case 'B':
        std::cout << YN_[odt.run_no_split(l, r, [&](auto itl, auto itr) {
          if (itl != itr) return false;
          if (!(l != 1 && r != n)) return true;
          if (l > itl->l && r < itl->r) return false;
          if (l == itl->l && r != itl->r) return std::prev(itl)->v != itl->v;
          if (l != itl->l && r == itl->r) return std::next(itl)->v != itl->v;
          return std::prev(itl)->v != std::next(itl)->v;
        })] << '\n';
    }
  }
  return 0;
}
