#include <bits/stdc++.h>
using namespace std;
template <typename Val_t = int,
          typename ID_t = int,
          const std::size_t _Edge_len = 500 + 5,
          const std::size_t _Node_size = 7000 + 5>
class DLX {
private:
  struct Node {
    ID_t l, r, u, d;
    ID_t row, col;
  } node[_Node_size];
  std::size_t width, height;
  std::size_t cnt_node;
  std::size_t cnt_col[_Edge_len];
#define __l(id) node[id].l
#define __r(id) node[id].r
#define __u(id) node[id].u
#define __d(id) node[id].d
#define __row(id) node[id].row
#define __col(id) node[id].col
#define _for(i, start, dir) \
  for (std::size_t i = __##dir(start); i != start; i = __##dir(i))
  void remove_col(std::size_t _col) {
    __r(__l(_col)) = __r(_col);
    __l(__r(_col)) = __l(_col);
    _for(i, _col, d)
      _for(j, i, r) {
        __u(__d(j)) = __u(j);
        __d(__u(j)) = __d(j);
        --cnt_col[__col(j)];
      }
  }
  void restore_col(std::size_t _col) {
    __r(__l(_col)) = __l(__r(_col)) = _col;
    _for(i, _col, u)
      _for(j, i, r) {
        __u(__d(j)) = __d(__u(j)) = j;
        ++cnt_col[__col(j)];
      }
  }
  std::size_t find_min_col() {
    std::size_t res = __r(0);
    _for(i, 0, r)
      if (cnt_col[i] < cnt_col[res]) res = i;
    return res;
  }
  bool dance(ID_t *_ans, std::size_t &_len) {
    if (__r(0) == 0) return true;
    std::size_t now_r = find_min_col();
    remove_col(now_r);
    _for(i, now_r, d) {
      _ans[++_len] = __row(i);
      _for(j, i, r) remove_col(__col(j));
      if (dance(_ans, _len)) return true;
      --_len;
      _for(j, i, l) restore_col(__col(j));
    }
    restore_col(now_r);
    return false;
  }

public:
  void clear() {
    memset(node, 0, sizeof(node));
    memset(cnt_col, 0, sizeof(cnt_col));
    width = height = cnt_node = 0;
  }
  void init(std::size_t _width, std::size_t _height) {
    width = cnt_node = _width;
    height = _height;
    for (std::size_t i = 1; i <= width; ++i)
      node[i] = {i - 1, i + 1, i, i, 0, i};
    node[__r(width) = 0] = {width, 1, 0, 0, 0, 0};
  }
  void insert_row(std::size_t _ln, ID_t *_cols, std::size_t _len_cols) {
    for (std::size_t i = 1; i <= _len_cols; ++i) {
      node[cnt_node + i] = {cnt_node + i - 1,
                            cnt_node + i + 1,
                            __u(_cols[i]),
                            _cols[i],
                            _ln,
                            _cols[i]};
      __d(__u(_cols[i])) = cnt_node + i;
      __u(_cols[i]) = cnt_node + i;
      ++cnt_col[_cols[i]];
      if (__d(_cols[i]) == _cols[i]) __d(_cols[i]) = cnt_node + i;
    }
    __l(cnt_node + 1) = cnt_node + _len_cols;
    __r(cnt_node + _len_cols) = cnt_node + 1;
    cnt_node += _len_cols;
  }
  void insert_map(Val_t **_map,
                  std::size_t _width,
                  std::size_t _height,
                  std::size_t _height_phy = _Edge_len) {
    ID_t *_ = (ID_t *)malloc(sizeof(ID_t) * (_width + 1));
    for (std::size_t _ln = 1, len; _ln <= _height; ++_ln) {
      len = 0;
      for (std::size_t _col = 1; _col <= _width; ++_col)
        if (*((Val_t *)_map + _ln * _height_phy + _col)) _[++len] = _col;
      if (len) insert_row(_ln, _, len);
    }
    free(_);
  }
  bool operator()(ID_t *ans, std::size_t &len) {
    len = 0;
    return dance(ans, len);
  }
#undef __l
#undef __r
#undef __u
#undef __d
#undef __row
#undef __col
#undef _for
};
DLX<> a;
const int N = 505;
int n, m;
int maps[N][N];
int ans[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) cin >> maps[i][j];
  a.init(m, n);
  a.insert_map((int **)maps, m, n, N);
  std::size_t len_ans = 0;
  if (a((int *)ans, len_ans))
    for (int i = 1; i <= len_ans; ++i) cout << ans[i] << " ";
  else cout << "No Solution!";
  return 0;
}
