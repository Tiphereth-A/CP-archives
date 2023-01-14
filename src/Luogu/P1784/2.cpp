#include <bits/stdc++.h>
using namespace std;
class DLX {
protected:
  struct Node {
    size_t l, r, u, d, row, col;
    constexpr Node(size_t l = 0,
                   size_t r = 0,
                   size_t u = 0,
                   size_t d = 0,
                   size_t row = 0,
                   size_t col = 0)
      : l(l), r(r), u(u), d(d), row(row), col(col) {}
    friend std::ostream &operator<<(std::ostream &os, Node const &data) {
      return os << data.l << ' ' << data.r << ' ' << data.u << ' ' << data.d
                << ' ' << data.row << ' ' << data.col;
    }
  };
  std::vector<Node> data;
  std::vector<size_t> cnt_col;
  bool multians;
#define l_(x) data[x].l
#define r_(x) data[x].r
#define u_(x) data[x].u
#define d_(x) data[x].d
#define row_(x) data[x].row
#define col_(x) data[x].col
#define for_(i, start, dir)                                         \
  for (size_t start__ = (start), i = dir##_(start__); i != start__; \
       i = dir##_(i))
  void remove_(size_t col) {
    r_(l_(col)) = r_(col);
    l_(r_(col)) = l_(col);
    for_(i, col, d)
      for_(j, i, r) {
        u_(d_(j)) = u_(j);
        d_(u_(j)) = d_(j);
        --cnt_col[col_(j)];
      }
  }
  void resume_(size_t col) {
    r_(l_(col)) = l_(r_(col)) = col;
    for_(i, col, u)
      for_(j, i, r) {
        u_(d_(j)) = d_(u_(j)) = j;
        ++cnt_col[col_(j)];
      }
  }
  bool dance_(std::vector<size_t> &ans_) {
    size_t now = r_(0);
    if (now == 0) return true;
    for_(i, 0, r)
      if (cnt_col[i] < cnt_col[now]) now = i;
    remove_(now);
    bool ret = false;
    for_(i, now, d) {
      ans_.push_back(row_(i));
      for_(j, i, r) remove_(col_(j));
      ret |= dance_(ans_);
      for_(j, i, l) resume_(col_(j));
      if (!multians && ret) return true;
      ans_.pop_back();
    }
    resume_(now);
    return ret;
  }
  void ins_row_(size_t row, const std::vector<size_t> &cols) {
    assert(row > 0);
    size_t sz = data.size();
    for (size_t i = 0; i < cols.size(); ++i) {
      data.emplace_back(
        sz + i - 1, sz + i + 1, u_(cols[i]), cols[i], row, cols[i]);
      u_(cols[i]) = d_(u_(cols[i])) = sz + i;
      ++cnt_col[cols[i]];
      if (d_(cols[i]) == cols[i]) d_(cols[i]) = sz + i;
    }
    r_(l_(sz) = data.size() - 1) = sz;
  }

public:
  explicit DLX(size_t width, bool multi_ans = false)
    : data(), cnt_col(), multians(multi_ans) {
    reset(width);
  }
  explicit DLX(std::vector<std::vector<bool>> const &grid,
               bool multi_ans = false)
    : data(), cnt_col(), multians(multi_ans) {
    reset_grid(grid);
  }
  friend std::ostream &operator<<(std::ostream &os, DLX const &dlx) {
    os << dlx.data[0].l << ' ' << dlx.cnt_col.size() << ' ' << dlx.data.size()
       << '\n';
    for (size_t i = 1; i < dlx.cnt_col.size(); ++i)
      os << dlx.cnt_col[i] << " \n"[i == dlx.cnt_col.size() - 1];
    for (size_t i = 0; i < dlx.data.size(); ++i)
      os << i << ": " << dlx.data[i] << '\n';
    return os;
  }
  void reset(size_t width) {
    assert(width > 0);
    data.clear();
    cnt_col.resize(width + 1, 0);
    for (size_t i = 0; i <= width; ++i)
      data.emplace_back(i - 1, i + 1, i, i, 0, i);
    r_(l_(0) = width) = 0;
  }
  void reset_grid(std::vector<std::vector<bool>> const &grid) {
    size_t col = grid[0].size();
    for (size_t i = 1; i < grid.size(); ++i)
      col = std::max(col, grid[i].size());
    reset(col);
    std::vector<size_t> _;
    for (size_t i = 0; i < grid.size(); ++i) {
      _.clear();
      for (size_t j = 0; j < grid[i].size(); ++j)
        if (grid[i][j]) _.push_back(j + 1);
      if (!_.empty()) ins_row_(i + 1, _);
    }
  }
  std::pair<bool, std::vector<size_t>> dance() {
    std::vector<size_t> ans;
    return {dance_(ans), ans};
  }
#undef l_
#undef r_
#undef u_
#undef d_
#undef row_
#undef col_
#undef for_
};
int sdk[9][9];
template <class Ch,
          class Tr,
          class Ct,
          std::enable_if_t<std::is_same_v<decltype(std::declval<Ct>().begin()),
                                          typename Ct::iterator> &&
                           std::is_same_v<decltype(std::declval<Ct>().end()),
                                          typename Ct::iterator>> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) cin >> sdk[i][j];
  vector<vector<bool>> maps(729, vector<bool>(324));
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) {
      for (int k = 1; k <= 9; ++k) {
        if (sdk[i][j] && sdk[i][j] != k) continue;
        auto _ = (k - 1) * 81 + i * 9 + j;
        maps[_][i * 9 + j] = maps[_][i * 9 + k + 80] =
          maps[_][j * 9 + k + 161] =
            maps[_][(i / 3 * 3 + j / 3) * 9 + k + 242] = true;
      }
    }
  auto &&[flag, res] = DLX(maps).dance();
  for (auto &&_ : res) {
    auto k = (_ - 1) / 81 + 1, i = (_ - 1) % 81 / 9, j = (_ - 1) % 9;
    sdk[i][j] = k;
  }
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) cout << sdk[i][j] << " \n"[j == 8];
  return 0;
}
