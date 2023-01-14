#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const i64 MOD = 1e9 + 7;
template <size_t N>
class Segtree {
  using data_type = i64;
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define _mid(l, r) (((l) + (r)) >> 1)
  struct Node {
    data_type a, a_sqr;
    Node(data_type _a = 0, data_type _a_sqr = 0): a(_a), a_sqr(_a_sqr) {}
    Node operator+(const Node &oth) const {
      Node _(*this);
      _.a += oth.a;
      _.a_sqr += oth.a_sqr;
      return _;
    }
  };
  int n;
  Node data[N << 2];
  data_type tag[N << 2];
  void _push_up(int p) { data[p] = data[_lch(p)] + data[_rch(p)]; }
  void _push_down(int p, i64 len_l, i64 len_r) {
    if (!tag[p]) return;
    data[_lch(p)] = {data[_lch(p)].a + tag[p] * len_l,
                     data[_lch(p)].a_sqr + data[_lch(p)].a * tag[p] * 2 +
                       tag[p] * tag[p] * len_l};
    data[_rch(p)] = {data[_rch(p)].a + tag[p] * len_r,
                     data[_rch(p)].a_sqr + data[_rch(p)].a * tag[p] * 2 +
                       tag[p] * tag[p] * len_r};
    tag[_lch(p)] += tag[p];
    tag[_rch(p)] += tag[p];
    tag[p] = 0;
  }
  void _init(int p, int l, int r) {
    if (l == r) {
      data_type a;
      std::cin >> a;
      data[p] = {a, a * a};
      return;
    }
    _init(_lch(p), l, _mid(l, r));
    _init(_rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  void _update(data_type k, int L, int R, int p, int l, int r) {
    if (L <= l && r <= R) {
      (data[p] = {data[p].a + k * (r - l + 1),
                  data[p].a_sqr + data[p].a * 2 * k + k * k * (r - l + 1)});
      (tag[p] += k);
      return;
    }
    _push_down(p, _mid(l, r) - l + 1, r - _mid(l, r));
    if (L <= _mid(l, r)) _update(k, L, R, _lch(p), l, _mid(l, r));
    if (R > _mid(l, r)) _update(k, L, R, _rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  data_type _query(int L, int R, int type, int p, int l, int r) {
    if (L <= l && r <= R) return type == 2 ? data[p].a : data[p].a_sqr;
    _push_down(p, _mid(l, r) - l + 1, r - _mid(l, r));
    data_type res = 0;
    if (L <= _mid(l, r)) (res += _query(L, R, type, _lch(p), l, _mid(l, r)));
    if (R > _mid(l, r)) (res += _query(L, R, type, _rch(p), _mid(l, r) + 1, r));
    return res;
  }

public:
  void init(int n) { _init(1, 1, this->n = n); }
  void update(data_type k, int L, int R) { _update(k, L, R, 1, 1, n); }
  data_type query(int L, int R, int type) {
    return _query(L, R, type, 1, 1, n);
  }
};
Segtree<N> tr;
i64 inv(i64 a) {
  i64 res(1), b(MOD - 2);
  for (; b; b >>= 1, (a *= a))
    if (b & 1) (res *= a);
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  tr.init(n);
  i64 op, l, r;
  i64 v;
  i64 x, y, z, g;
  while (m--) {
    cin >> op >> l >> r;
    switch (op) {
      case 1:
        cin >> v;
        tr.update(v, l, r);
        break;
      case 2:
        x = tr.query(l, r, op);
        y = (r - l + 1);
        g = __gcd(x, y);
        x /= g;
        y /= g;
        if (x == 0) y = 1;
        cout << x << '/' << y << '\n';
        break;
      case 3:
        z = tr.query(l, r, 2);
        x = tr.query(l, r, 3) * (r - l + 1) - z * z;
        y = (r - l + 1) * (r - l + 1);
        g = __gcd(x, y);
        x /= g;
        y /= g;
        if (x == 0) y = 1;
        cout << x << '/' << y << '\n';
        break;
    }
  }
  return 0;
}
