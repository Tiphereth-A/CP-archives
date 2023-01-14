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
    friend std::ostream &operator<<(std::ostream &os, Node const &node) {
      return os << node.l << ' ' << node.r << ' ' << node.u << ' ' << node.d
                << ' ' << node.row << ' ' << node.col;
    }
  };
  std::vector<Node> node;
  std::vector<size_t> cnt_col;
  size_t width, height;
#define l_(id) node[id].l
#define r_(id) node[id].r
#define u_(id) node[id].u
#define d_(id) node[id].d
#define row_(id) node[id].row
#define col_(id) node[id].col
#define for_(i, start, dir) \
  for (size_t i = dir##_(start); i != start; i = dir##_(i))
  void remove_col(size_t now_col_) {
    r_(l_(now_col_)) = r_(now_col_);
    l_(r_(now_col_)) = l_(now_col_);
    for_(i, now_col_, d)
      for_(j, i, r) {
        u_(d_(j)) = u_(j);
        d_(u_(j)) = d_(j);
        --cnt_col[col_(j)];
      }
  }
  void resume_col(size_t now_col_) {
    r_(l_(now_col_)) = l_(r_(now_col_)) = now_col_;
    for_(i, now_col_, u)
      for_(j, i, r) {
        u_(d_(j)) = d_(u_(j)) = j;
        ++cnt_col[col_(j)];
      }
  }
  size_t find_min_col() {
    size_t res = r_(0);
    for_(i, 0, r)
      if (cnt_col[i] < cnt_col[res]) res = i;
    return res;
  }
  bool dance_(std::vector<size_t> &ans_) {
    if (r_(0) == 0) return true;
    size_t now_r = find_min_col();
    remove_col(now_r);
    for_(i, now_r, d) {
      ans_.push_back(row_(i));
      for_(j, i, r) remove_col(col_(j));
      if (dance_(ans_)) {
        for_(j, i, l) resume_col(col_(j));
        return true;
      }
      ans_.pop_back();
      for_(j, i, l) resume_col(col_(j));
    }
    resume_col(now_r);
    return false;
  }
  void insert_row(size_t ln_, const std::vector<size_t> &cols_) {
    assert(ln_ > 0);
    size_t sz = node.size();
    for (size_t i = 0; i < cols_.size(); ++i) {
      node.emplace_back(
        sz + i - 1, sz + i + 1, u_(cols_[i]), cols_[i], ln_, cols_[i]);
      d_(u_(cols_[i])) = sz + i;
      u_(cols_[i]) = sz + i;
      ++cnt_col[cols_[i]];
      if (d_(cols_[i]) == cols_[i]) d_(cols_[i]) = sz + i;
    }
    l_(sz) = sz + cols_.size() - 1;
    r_(sz + cols_.size() - 1) = sz;
  }

public:
  DLX(): node(), cnt_col(), width(0), height(0) {}
  DLX(size_t row, size_t col): DLX() { reset(row, col); }
  DLX(size_t row, size_t col, std::vector<std::vector<bool>> const &grid)
    : DLX() {
    reset_grid(row, col, grid);
  }
  friend std::ostream &operator<<(std::ostream &os, DLX const &dlx) {
    os << dlx.width << ' ' << dlx.height << ' ' << dlx.node.size() << '\n';
    for (size_t i = 1; i <= dlx.width; ++i)
      os << dlx.cnt_col[i] << " \n"[i == dlx.width];
    for (size_t i = 0; i < dlx.node.size(); ++i)
      os << i << ": " << dlx.node[i] << '\n';
    return os;
  }
  void clear() {
    node.clear();
    cnt_col.clear();
    width = height = 0;
  }
  void reset(size_t row, size_t col) {
    clear();
    width = col;
    height = row;
    cnt_col.resize(height + 1);
    node.emplace_back(width, 1, 0, 0, 0, 0);
    for (size_t i = 1; i <= width; ++i)
      node.emplace_back(i - 1, i + 1, i, i, 0, i);
    r_(width) = 0;
  }
  void reset_grid(size_t row,
                  size_t col,
                  std::vector<std::vector<bool>> const &grid) {
    reset(row, col);
    std::vector<size_t> _;
    for (size_t i = 0; i < row; ++i) {
      _.clear();
      for (size_t j = 0; j < col; ++j)
        if (grid[i][j]) _.push_back(j + 1);
      if (!_.empty()) insert_row(i + 1, _);
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
  DLX a(n, m, maps);
  auto &&res = a.dance();
  if (res.first)
    for (auto &&i : res.second) cout << i << ' ';
  else cout << "No Solution!";
  return 0;
}
