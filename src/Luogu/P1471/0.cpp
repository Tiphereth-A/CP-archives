#include <bits/stdc++.h>
using namespace std;
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
template <size_t N>
class Segtree {
  using data_type = double;
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
  void _push_down(int p, int len) {
    if (!tag[p]) return;
    data[_lch(p)] = {data[_lch(p)].a + tag[p] * (len - len / 2),
                     data[_lch(p)].a_sqr + data[_lch(p)].a * 2 * tag[p] +
                       tag[p] * tag[p] * (len - len / 2)};
    data[_rch(p)] = {data[_rch(p)].a + tag[p] * (len / 2),
                     data[_rch(p)].a_sqr + data[_rch(p)].a * 2 * tag[p] +
                       tag[p] * tag[p] * (len / 2)};
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
      data[p] = {data[p].a + k * (r - l + 1),
                 data[p].a_sqr + data[p].a * 2 * k + k * k * (r - l + 1)};
      tag[p] += k;
      return;
    }
    _push_down(p, r - l + 1);
    if (L <= _mid(l, r)) _update(k, L, R, _lch(p), l, _mid(l, r));
    if (R > _mid(l, r)) _update(k, L, R, _rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  data_type _query(int L, int R, int type, int p, int l, int r) {
    if (L <= l && r <= R) return type == 2 ? data[p].a : data[p].a_sqr;
    _push_down(p, r - l + 1);
    data_type res = 0;
    if (L <= _mid(l, r)) res += _query(L, R, type, _lch(p), l, _mid(l, r));
    if (R > _mid(l, r)) res += _query(L, R, type, _rch(p), _mid(l, r) + 1, r);
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
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cout << fixed << setprecision(4);
  tr.init(n);
  int op, l, r;
  double v;
  while (m--) {
    cin >> op >> l >> r;
    switch (op) {
      case 1:
        cin >> v;
        tr.update(v, l, r);
        break;
      case 2: cout << tr.query(l, r, op) / (r - l + 1) << '\n'; break;
      case 3:
        double x = tr.query(l, r, 3) / (r - l + 1),
               y = tr.query(l, r, 2) / (r - l + 1);
        cout << x - y * y << '\n';
        break;
    }
  }
  return 0;
}
