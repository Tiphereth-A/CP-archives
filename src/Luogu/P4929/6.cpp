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
  size_t min_id_() {
    size_t res = r_(0);
    for_(i, 0, r)
      if (cnt_col[i] < cnt_col[res]) res = i;
    return res;
  }
  bool dance_(std::vector<size_t> &ans_) {
    if (r_(0) == 0) return true;
    size_t now = min_id_();
    remove_(now);
    for_(i, now, d) {
      ans_.push_back(row_(i));
      for_(j, i, r) remove_(col_(j));
      if (dance_(ans_)) {
        for_(j, i, l) resume_(col_(j));
        return true;
      }
      ans_.pop_back();
      for_(j, i, l) resume_(col_(j));
    }
    resume_(now);
    return false;
  }
  void ins_row_(size_t row, const std::vector<size_t> &cols) {
    assert(row > 0);
    size_t sz = data.size();
    for (size_t i = 0; i < cols.size(); ++i) {
      data.emplace_back(
        sz + i - 1, sz + i + 1, u_(cols[i]), cols[i], row, cols[i]);
      d_(u_(cols[i])) = sz + i;
      u_(cols[i]) = sz + i;
      ++cnt_col[cols[i]];
      if (d_(cols[i]) == cols[i]) d_(cols[i]) = sz + i;
    }
    r_(l_(sz) = sz + cols.size() - 1) = sz;
  }

public:
  explicit DLX(size_t width): data(), cnt_col() { reset(width); }
  explicit DLX(std::vector<std::vector<bool>> const &grid): data(), cnt_col() {
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
    cnt_col.resize(width + 1, 0);
    data.resize(1, {width, 1, 0, 0, 0, 0});
    for (size_t i = 1; i <= width; ++i)
      data.emplace_back(i - 1, i + 1, i, i, 0, i);
    r_(width) = 0;
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
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<bool>> maps(n, vector<bool>(m));
  for (int i = 0, x; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      cin >> x;
      maps[i][j] = x;
    }
  DLX a(maps);
  auto &&res = a.dance();
  if (res.first)
    for (auto &&i : res.second) cout << i << ' ';
  else cout << "No Solution!";
  return 0;
}
