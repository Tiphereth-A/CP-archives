#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  x = 0;
  char ch;
  while (!isdigit(ch = getc()));
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
const int N = 2e5 + 5;
i64 a[N];
template <size_t N>
class Segtree {
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
  struct Node {
    double n_sin, n_cos;
    Node(double _sin = 0, double _cos = 0): n_sin(_sin), n_cos(_cos) {}
    Node operator+(const Node &oth) const {
      Node _(*this);
      _.n_sin += oth.n_sin;
      _.n_cos += oth.n_cos;
      return _;
    }
    Node &operator+=(i64 x) {
      double _sin = this->n_sin, _cos = this->n_cos;
      this->n_sin = _sin * std::cos(x) + _cos * std::sin(x);
      this->n_cos = _cos * std::cos(x) - _sin * std::sin(x);
      return *this;
    }
  };
  int n;
  Node data[N << 2];
  i64 tag[N << 2];
  void _push_up(int p) { data[p] = data[_lch(p)] + data[_rch(p)]; }
  void _push_down(int p) {
    if (!tag[p]) return;
    data[_lch(p)] += tag[p];
    data[_rch(p)] += tag[p];
    tag[_lch(p)] += tag[p];
    tag[_rch(p)] += tag[p];
    tag[p] = 0;
  }
  void _init(int p, int l, int r) {
    if (l == r) {
      data[p] = {std::sin(a[l]), std::cos(a[l])};
      return;
    }
    _init(_lch(p), l, _mid(l, r));
    _init(_rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  void _update(i64 k, int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) {
      data[p] += k;
      tag[p] += k;
      return;
    }
    _push_down(p);
    if (L <= _mid(l, r)) _update(k, L, R, _lch(p), l, _mid(l, r));
    if (R > _mid(l, r)) _update(k, L, R, _rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  double _query(int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) return data[p].n_sin;
    _push_down(p);
    double res = 0;
    if (L <= _mid(l, r)) res += _query(L, R, _lch(p), l, _mid(l, r));
    if (R > _mid(l, r)) res += _query(L, R, _rch(p), _mid(l, r) + 1, r);
    return res;
  }

public:
  void init(int n) { _init(1, 1, this->n = n); }
  void update(int k, int L, int R) { _update(k, L, R, 1, 1, n); }
  double query(int L, int R) { return _query(L, R, 1, 1, n); }
};
Segtree<N> tr;
int main() {
  int n, m;
  read(n);
  _for(i, 1, n) read(a[i]);
  tr.init(n);
  read(m);
  i64 op, l, r, v;
  while (m--) {
    read(op, l, r);
    if (op & 1) {
      read(v);
      tr.update(v, l, r);
    } else printf("%.1lf\n", tr.query(l, r));
  }
  return 0;
}
