#include <bits/stdc++.h>
namespace tifa_libs {
using u32 = uint32_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
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
void solve() {
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  tifa_libs::vvec<bool> maps(n, tifa_libs::vec<bool>(m));
  for (size_t i = 0, x; i < n; ++i)
    for (size_t j = 0; j < m; ++j) {
      std::cin >> x;
      maps[i][j] = x;
    }
  auto res =
    tifa_libs::util::DLX(maps).dance([]([[maybe_unused]] auto const &x) {});
  if (res.has_value())
    for (auto i : res.value()) std::cout << i << ' ';
  else std::cout << "No Solution!";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}
