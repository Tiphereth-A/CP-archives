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
namespace PieceOperation {
constexpr uint32_t flip4(uint32_t x) {
  return (x & 1) << 3 | ((x >> 1) & 1) << 2 | ((x >> 2) & 1) << 1 |
         ((x >> 3) & 1);
}
constexpr uint32_t expand4(uint32_t x) {
  return (x & 8) << 9 | (x & 4) << 6 | (x & 2) << 3 | (x & 1);
}
constexpr uint32_t flip16(uint32_t x) {
  return flip4((x >> 12) & 15) << 12 | flip4((x >> 8) & 15) << 8 |
         flip4((x >> 4) & 15) << 4 | flip4(x & 15);
}
constexpr uint32_t rot16(uint32_t x) {
  return expand4(flip4((x >> 12) & 15)) << 3 |
         expand4(flip4((x >> 8) & 15)) << 2 |
         expand4(flip4((x >> 4) & 15)) << 1 | expand4(flip4(x & 15));
}
constexpr uint32_t rearrange16(uint32_t x) {
  assert(x);
  while (!(x & 0xf000)) x <<= 4;
  while (!(x & 0x8888))
    x = (((x >> 12) & 7) << 13) | (((x >> 8) & 7) << 9) |
        (((x >> 4) & 7) << 5) | ((x & 7) << 1);
  return x;
}
const uint32_t pieces_base[] = {0x1c800,
                                0x2f000,
                                0x3e800,
                                0x4cc00,
                                0x588e0,
                                0x6f400,
                                0x7ea00,
                                0x8ec00,
                                0x9e300,
                                0xa4e40,
                                0xb8c60,
                                0xcf800};
constexpr uint32_t flip(uint32_t piece) {
  return (piece & 0xf0000) | rearrange16(flip16(piece & 0xffff));
}
constexpr uint32_t rotate(uint32_t piece) {
  return (piece & 0xf0000) | rearrange16(rot16(piece & 0xffff));
}
std::vector<uint32_t> getall() {
  std::set<uint32_t> s;
  for (auto &&i : pieces_base)
    s.merge(std::set<uint32_t>{i,
                               rotate(i),
                               rotate(rotate(i)),
                               rotate(rotate(rotate(i))),
                               flip(i),
                               rotate(flip(i)),
                               rotate(rotate(flip(i))),
                               rotate(rotate(rotate(flip(i))))});
  std::vector<uint32_t> ans;
  for (auto &&j : s) ans.push_back(j);
  return ans;
}
}  // namespace PieceOperation
const uint32_t pieces[60] = {
  0x14c00, 0x18c00, 0x1c400, 0x1c800, 0x28888, 0x2f000, 0x32e00, 0x344c0,
  0x388c0, 0x38e00, 0x3c440, 0x3c880, 0x3e200, 0x3e800, 0x4cc00, 0x522e0,
  0x588e0, 0x5e220, 0x5e880, 0x62f00, 0x644c4, 0x64c44, 0x64f00, 0x688c8,
  0x68c88, 0x6f200, 0x6f400, 0x7ae00, 0x7c4c0, 0x7c8c0, 0x7ea00, 0x84cc0,
  0x86e00, 0x88cc0, 0x8cc40, 0x8cc80, 0x8ce00, 0x8e600, 0x8ec00, 0x93e00,
  0x944c8, 0x94c88, 0x97c00, 0x988c4, 0x98c44, 0x9c700, 0x9e300, 0xa4e40,
  0xb26c0, 0xb6c80, 0xb8c60, 0xbc620, 0xc1f00, 0xc444c, 0xc888c, 0xc8f00,
  0xcc444, 0xcc888, 0xcf100, 0xcf800};
class Board {
protected:
  uint64_t data[10] = {};
  bool pplaced[16] = {};
  uint32_t pcord[16][2] = {{10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10},
                           {10, 10}};

public:
  constexpr Board() = default;
  friend std::istream &operator>>(std::istream &is, Board &board) {
    std::string s;
    for (uint64_t _ = 0xfffffffff, i = 0; i < 10; ++i, _ >>= 4) {
      is >> s;
      board.data[i] = _;
      for (size_t j = 0; j <= i; ++j)
        if (isalpha(s[j])) {
          board.pplaced[s[j] & 15] = true;
          auto &coord = board.pcord[s[j] & 15];
          coord[0] = std::min(coord[0], (uint32_t)i);
          coord[1] = std::min(coord[1], (uint32_t)j);
          board.data[i] |= (s[j] & 15ull) << (4 * (9 - j));
        }
    }
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, Board const &board) {
    uint32_t _;
    for (size_t i = 0; i < 10; ++i) {
      for (size_t j = 0; j <= i; ++j)
        os << ((_ = board.get(i, j)) ? (char)(_ + '@') : '.');
      os << '\n';
    }
    return os;
  }
  constexpr uint32_t get(size_t row, size_t col) const {
    assert(row < 10 && col <= row);
    return (data[row] >> (4 * (9 - col))) & 15;
  }
  constexpr bool can_place_4x4(size_t row, size_t col, size_t piece) const {
    if (row > 9 || col > row) return false;
    auto &&pid = (piece >> 16) & 15;
    if (pplaced[pid]) {
      if (row != pcord[pid][0] || col != pcord[pid][1]) return false;
    } else pid = 0;
    size_t p[4] = {
      (piece >> 12) & 15, (piece >> 8) & 15, (piece >> 4) & 15, piece & 15};
    for (size_t i = 0, s = 0, end_ = !!p[0] + !!p[1] + !!p[2] + !!p[3];
         i < end_;
         ++i) {
      if (row + i > 9) return false;
      ptrdiff_t ofs = 4 * (6 - (ptrdiff_t)col);
      s = (ofs < 0 ? (data[row + i] << -ofs | ((1ull << -ofs) - 1)) :
                     (data[row + i] >> ofs)) &
          0xffff;
      s = (((s >> 12) & 15) == pid) << 3 | (((s >> 8) & 15) == pid) << 2 |
          (((s >> 4) & 15) == pid) << 1 | ((s & 15) == pid);
      if (p[i] & (p[i] ^ s)) return false;
    }
    return true;
  }
  constexpr void place_4x4(size_t row, size_t col, size_t piece) {
    auto &&pid = (piece >> 16) & 15;
    for (size_t i = row; i < std::min((size_t)10, row + 4); ++i)
      for (size_t j = col; j < std::min((size_t)10, col + 4); ++j)
        data[i] |= ((pid * !!(piece & (1 << (15 - (i - row) * 4 - j + col))))
                    << (4 * (9 - j)));
  }
};
int main() {
  Board board;
  cin >> board;
  vector<vector<bool>> maps;
  vector<tuple<size_t, size_t, size_t>> coord;
  {
    auto encode = [](size_t row, size_t col) {
      return 12 + row * (row + 1) / 2 + col;
    };
    vector<bool> _;
    for (size_t id = 0; id < sizeof(pieces) / sizeof(pieces[0]); ++id)
      for (size_t i = 0; i < 10; ++i)
        for (size_t j = 0; j <= i; ++j)
          if (board.can_place_4x4(i, j, pieces[id])) {
            _.clear();
            _.resize(67);
            _[((pieces[id] >> 16) & 15) - 1] = 1;
            for (size_t _i = 0; _i < 4; ++_i)
              for (size_t _j = 0; _j < 4; ++_j)
                _[encode(i + _i, j + _j)] =
                  pieces[id] & (1 << (15 - _i * 4 - _j));
            coord.emplace_back(id, i, j);
            maps.push_back(_);
          }
  }
  auto &&[f, res] = DLX(maps).dance();
  if (!f) {
    cout << "No solution";
    return 0;
  }
  for (auto &&x : res) {
    auto &&[id, i, j] = coord[x - 1];
    board.place_4x4(i, j, pieces[id]);
  }
  cout << board;
  return 0;
}
