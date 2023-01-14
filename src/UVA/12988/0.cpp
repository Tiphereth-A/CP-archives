#include <bits/stdc++.h>
namespace SUDOKU {
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
  bool dance_(std::vector<size_t> &ans_,
              std::function<void(std::vector<size_t> const &)> const &func_) {
    size_t now = r_(0);
    if (now == 0) return func_(ans_), true;
    for_(i, 0, r)
      if (cnt_col[i] < cnt_col[now]) now = i;
    remove_(now);
    bool ret = false;
    for_(i, now, d) {
      ans_.push_back(row_(i));
      for_(j, i, r) remove_(col_(j));
      ret |= dance_(ans_, func_);
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
  std::pair<bool, std::vector<size_t>>
  dance(std::function<void(std::vector<size_t> const &)> func =
          [](std::vector<size_t> const &) {}) {
    std::vector<size_t> ans;
    return {dance_(ans, func), ans};
  }
#undef l_
#undef r_
#undef u_
#undef d_
#undef row_
#undef col_
#undef for_
};
template <size_t N>
class Sudoku {
  static_assert(N > 0);
  static constexpr size_t N2 = N * N, N4 = N2 * N2;
  using self = Sudoku<N>;
  using data_t = std::array<std::array<size_t, N2>, N2>;

protected:
  data_t data;

public:
  Sudoku(): data() {}
  friend std::istream &operator>>(std::istream &is, self &sdk) {
    for (size_t i = 0; i < N2; ++i)
      for (size_t j = 0; j < N2; ++j) is >> sdk.data[i][j];
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, self const &sdk) {
    for (size_t i = 0; i < N2; ++i)
      for (size_t j = 0; j < N2; ++j) {
        os << sdk.data[i][j];
        if (i != N2 - 1 || j != N2 - 1) os << " \n"[j == N2 - 1];
      }
    return os;
  }
  void set(size_t row, size_t col, size_t val) {
    assert(row < N2 && col < N2 && val <= N2);
    data[row][col] = val;
  }
  size_t get(size_t row, size_t col) const { return data[row][col]; }
  std::vector<self> solve(bool get_all_solution = false) {
    std::vector<std::vector<bool>> st(N2 * N4, std::vector<bool>(4 * N4));
    bool not_filled = true;
    for (size_t i = 0; i < N2; ++i)
      for (size_t j = 0; j < N2; ++j) {
        for (size_t k = 1; k <= N2; ++k) {
          if (data[i][j] && data[i][j] != k) continue;
          not_filled |= data[i][j] == 0;
          auto _ = (k - 1) * N4 + i * N2 + j;
          st[_][i * N2 + j] = st[_][i * N2 + k + N4 - 1] =
            st[_][j * N2 + k + N4 * 2 - 1] =
              st[_][(i / N * N + j / N) * N2 + k + N4 * 3 - 1] = true;
        }
      }
    std::vector<self> ans;
    if (!not_filled) {
      ans.push_back(*this);
      return ans;
    }
    auto func = [&ans](std::vector<size_t> const &res) {
      self sdk;
      for (auto &&_ : res)
        sdk.set((_ - 1) % N4 / N2, (_ - 1) % N2, (_ - 1) / N4 + 1);
      ans.push_back(sdk);
    };
    DLX dlx(st, get_all_solution);
    dlx.dance(func);
    return ans;
  }
};
}  // namespace SUDOKU
using SUDOKU::Sudoku;
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Sudoku<2> sdk;
  string s;
  int k;
  cin >> k;
  for (int t_ = 1; t_ <= k; ++t_) {
    cout << "Case #" << t_ << ":\n";
    for (int i = 0; i < 4; ++i) {
      cin >> s;
      for (int j = 0; j < 4; ++j) sdk.set(i, j, s[j] == '*' ? 0 : s[j] - '0');
    }
    auto &&res = sdk.solve();
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) cout << res[0].get(i, j);
      cout << '\n';
    }
  }
  return 0;
}
