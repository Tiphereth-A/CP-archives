#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 5e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
template <class _T = std::ptrdiff_t,
          const std::size_t __N = N,
          const bool _clear = false>
class SegTree {
private:
  struct Node {
    _T sum, max, lazy;
    Node operator+=(const Node &oth) {
      sum += oth.sum;
      lazy += oth.lazy;
      return *this;
    }
  } t[__N * 4];
  std::size_t n;
  void _push_up(std::size_t index) {
    t[index].sum = t[index << 1].sum + t[index << 1 | 1].sum;
    t[index].max = max(t[index << 1].max, t[index << 1 | 1].max);
  }
  void
  _push_down(std::size_t index, std::ptrdiff_t len_l, std::ptrdiff_t len_r) {
    if (t[index].lazy == 0) return;
    t[index << 1] += (Node){t[index].lazy * len_l, 0, t[index].lazy};
    t[index << 1 | 1] += (Node){t[index].lazy * len_r, 0, t[index].lazy};
    t[index].lazy = 0;
  }
  void _init(_T data[],
             std::size_t index = 1,
             std::size_t l = 1,
             std::size_t r = __N - 1) {
    if (l == r) {
      t[index].sum = t[index].max = data[l];
      return;
    }
    std::size_t mid = l + ((r - l) >> 1);
    _init(data, index << 1, l, mid);
    _init(data, index << 1 | 1, mid + 1, r);
    _push_up(index);
  }
  void _modify(std::size_t pos,
               _T k,
               std::size_t index = 1,
               std::size_t l = 1,
               std::size_t r = __N - 1) {
    if (l == r) {
      t[index].sum = t[index].max = k;
      return;
    }
    std::size_t mid = l + ((r - l) >> 1);
    _push_down(index, mid - l + 1, r - mid);
    if (mid >= pos) _modify(pos, k, index << 1, l, mid);
    else _modify(pos, k, index << 1 | 1, mid + 1, r);
    _push_up(index);
  }
  void _update(std::size_t L,
               std::size_t R,
               _T k,
               std::size_t index = 1,
               std::size_t l = 1,
               std::size_t r = __N - 1) {
    if (L <= l && r <= R) {
      if (t[index].max < k) return;
    }
    if (l == r) {
      t[index].sum = t[index].max = t[index].sum % k;
      return;
    }
    std::size_t mid = l + ((r - l) >> 1);
    _push_down(index, mid - l + 1, r - mid);
    if (mid >= L) _update(L, R, k, index << 1, l, mid);
    if (mid < R) _update(L, R, k, index << 1 | 1, mid + 1, r);
    _push_up(index);
  }
  _T _query(std::size_t L,
            std::size_t R,
            std::size_t index = 1,
            std::size_t l = 1,
            std::size_t r = __N - 1) {
    if (L <= l && r <= R) return t[index].sum;
    std::size_t mid = l + ((r - l) >> 1);
    _T ans = 0;
    _push_down(index, mid - l + 1, r - mid);
    if (mid >= L) ans += _query(L, R, index << 1, l, mid);
    if (mid < R) ans += _query(L, R, index << 1 | 1, mid + 1, r);
    return ans;
  }

public:
  SegTree(std::size_t _n = 0): n(_n) {
    if (_clear) memset(t, 0, sizeof t);
  }
  SegTree(_T Data[], std::size_t _n = 0): n(_n) {
    if (_clear) memset(t, 0, sizeof t);
    _init(Data, 1, 1, n);
  }
  void init(_T Data[], std::size_t _n) {
    n = _n;
    _init(Data, 1, 1, n);
  }
  void clear() { memset(t, n = 0, sizeof t); }
  void update(std::size_t Left, std::size_t Right, _T Val) {
    _update(Left, Right, Val, 1, 1, n);
  }
  void modify(std::size_t pos, _T val) { _modify(pos, val, 1, 1, n); }
  _T query(std::size_t Left, std::size_t Right) {
    return _query(Left, Right, 1, 1, n);
  }
};
i64 a[N];
SegTree<i64> st;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  _for(i, 1, n) scanf("%lld", a + i);
  st.init(a, n);
  int op;
  i64 l, r, x;
  _for(i, 1, m) {
    scanf("%d%lld%lld", &op, &l, &r);
    if (op == 1) printf("%lld\n", st.query(l, r));
    else if (op == 2) {
      scanf("%lld", &x);
      st.update(l, r, x);
    } else st.modify(l, r);
  }
FINISHED:
  return 0;
}
