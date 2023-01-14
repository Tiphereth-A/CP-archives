namespace tifa_libs::bit {
template <typename T>
constexpr int cntl0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  static_assert(nd <= 128);
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_clz(x) - (nd_u - nd);
  else if constexpr (nd <= nd_ul) return __builtin_clzl(x) - (nd_ul - nd);
  else if constexpr (nd <= nd_ull) return __builtin_clzll(x) - (nd_ull - nd);
  else {
    unsigned long long hi = x >> nd_ull;
    if (hi != 0) return __builtin_clzll(hi) - ((2 * nd_ull) - nd);
    unsigned long long lo = x & (unsigned long long)(-1);
    return (nd - nd_ull) + __builtin_clzll(lo);
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int bwidth(T x) {
  return (int)sizeof(T) * 8 - cntl0(x);
}
}  // namespace tifa_libs::bit
#include <bits/stdc++.h>
namespace tifa_libs {
using u32 = uint32_t;
using u64 = uint64_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using vvvec = vec<vvec<T>>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
namespace tifa_libs::math {
constexpr u32 isqrt(u64 x) {
  int c = (bit::bwidth(x) - 1) / 2, sh = 31 - c;
  u32 u = [](u64 x) {
    constexpr uint8_t TAB[192] = {
      128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
      143, 144, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155,
      156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
      167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178,
      179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 186, 186, 187, 188, 188,
      189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198,
      199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208,
      208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 216, 216, 217,
      217, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
      226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233, 234,
      234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 242,
      242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250,
      250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255};
    u32 u = TAB[(x >> 56) - 64];
    u = (u << 7) + (u32)(x >> 41) / u;
    return (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  u >>= sh;
  u -= (u64)u * u > x;
  return u;
}
}  // namespace tifa_libs::math
namespace tifa_libs::util {
class DLX {
  struct node {
    size_t l, r, u, d, row, col;
    constexpr node(size_t l = 0,
                   size_t r = 0,
                   size_t u = 0,
                   size_t d = 0,
                   size_t row = 0,
                   size_t col = 0)
      : l(l), r(r), u(u), d(d), row(row), col(col) {}
  };
  vec<node> data;
  vec<size_t> cnt_col;
  const bool mans;
#define l_(x) data[x].l
#define r_(x) data[x].r
#define u_(x) data[x].u
#define d_(x) data[x].d
#define row_(x) data[x].row
#define col_(x) data[x].col
#define dlxfor_(i, l, dir) \
  for (size_t ied__ = (l), i = dir##_(ied__); i != ied__; i = dir##_(i))
  void remove_(size_t col) {
    r_(l_(col)) = r_(col);
    l_(r_(col)) = l_(col);
    dlxfor_(i, col, d) dlxfor_(j, i, r) {
      u_(d_(j)) = u_(j);
      d_(u_(j)) = d_(j);
      --cnt_col[col_(j)];
    }
  }
  void resume_(size_t col) {
    r_(l_(col)) = l_(r_(col)) = col;
    dlxfor_(i, col, u) dlxfor_(j, i, r) {
      u_(d_(j)) = d_(u_(j)) = j;
      ++cnt_col[col_(j)];
    }
  }
  template <class F>
  bool dance_(vec<size_t> &ans, F cb) {
    size_t now = r_(0);
    if (now == 0) return cb(ans), true;
    dlxfor_(i, 0, r) if (cnt_col[i] < cnt_col[now]) now = i;
    remove_(now);
    bool ret = false;
    dlxfor_(i, now, d) {
      ans.push_back(row_(i));
      dlxfor_(j, i, r) remove_(col_(j));
      ret |= dance_(ans, cb);
      dlxfor_(j, i, l) resume_(col_(j));
      if (!mans && ret) return true;
      ans.pop_back();
    }
    resume_(now);
    return ret;
  }
  void ins_row_(size_t row, vec<size_t> const &cols) {
    assert(row > 0);
    size_t n = data.size();
    for (size_t i = 0; i < cols.size(); ++i) {
      data.emplace_back(
        n + i - 1, n + i + 1, u_(cols[i]), cols[i], row, cols[i]);
      u_(cols[i]) = d_(u_(cols[i])) = n + i;
      ++cnt_col[cols[i]];
      if (d_(cols[i]) == cols[i]) d_(cols[i]) = n + i;
    }
    r_(l_(n) = data.size() - 1) = n;
  }

public:
  explicit DLX(vvec<bool> const &grid, bool multi_ans = false)
    : data(), cnt_col(), mans(multi_ans) {
    size_t col = grid[0].size();
    assert(col > 0);
    cnt_col.resize(col + 1);
    data.reserve(col + 1);
    for (size_t i = 0; i <= col; ++i)
      data.emplace_back(i - 1, i + 1, i, i, 0, i);
    r_(l_(0) = col) = 0;
    for (size_t i = 0; i < grid.size(); ++i) {
      vec<size_t> _;
      _.reserve(col);
      for (size_t j = 0; j < col; ++j)
        if (grid[i][j]) _.push_back(j + 1);
      _.shrink_to_fit();
      if (!_.empty()) ins_row_(i + 1, _);
    }
  }
  template <class F>
  std::optional<vec<size_t>> dance(F cb) {
    vec<size_t> ans;
    if (!dance_(ans, cb)) return {};
    return ans;
  }
#undef l_
#undef r_
#undef u_
#undef d_
#undef row_
#undef col_
#undef dlxfor_
};
}  // namespace tifa_libs::util
namespace tifa_libs::game {
vvvec<size_t> sudoku_solver(vvec<size_t> const &data,
                            bool get_all_solution = false) {
  const size_t n = math::isqrt(data.size()), n2 = data.size(), n4 = n2 * n2;
  assert(n * n == n2);
  vvec<bool> g(n2 * n4, vec<bool>(4 * n4));
  bool not_filled = true;
  for (size_t i = 0; i < n2; ++i)
    for (size_t j = 0; j < n2; ++j)
      for (size_t k = 1; k <= n2; ++k) {
        if (data[i][j] && data[i][j] != k) continue;
        not_filled |= data[i][j] == 0;
        auto _ = (k - 1) * n4 + i * n2 + j;
        g[_][i * n2 + j] = g[_][i * n2 + k + n4 - 1] =
          g[_][j * n2 + k + n4 * 2 - 1] =
            g[_][(i / n * n + j / n) * n2 + k + n4 * 3 - 1] = true;
      }
  if (!not_filled) return {data};
  vvvec<size_t> ans;
  auto cb = [&data, &ans, n4, n2](vec<size_t> const &res) -> void {
    auto dt = data;
    for (auto _ : res) dt[(_ - 1) % n4 / n2][(_ - 1) % n2] = (_ - 1) / n4 + 1;
    ans.push_back(dt);
  };
  util::DLX(g, get_all_solution).dance(cb);
  return ans;
}
}  // namespace tifa_libs::game
void solve() {
  tifa_libs::vvec<size_t> sdk(9, tifa_libs::vec<size_t>(9));
  for (auto &i : sdk)
    for (auto &j : i) std::cin >> j;
  auto res = tifa_libs::game::sudoku_solver(sdk)[0];
  for (size_t i = 0; i < 9; ++i)
    for (size_t j = 0; j < 9; ++j) std::cout << res[i][j] << " \n"[j == 8];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}
