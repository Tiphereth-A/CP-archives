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
    Node &operator%=(const i64 &mod) {
      this->a %= mod;
      this->a_sqr %= mod;
      return *this;
    }
  };
  int n;
  Node data[N << 2];
  data_type tag[N << 2];
  void _push_up(int p) { (data[p] = data[_lch(p)] + data[_rch(p)]) %= MOD; }
  void _init(int p, int l, int r) {
    if (l == r) {
      data_type a;
      std::cin >> a;
      data[p] = {a, a * a % MOD};
      return;
    }
    _init(_lch(p), l, _mid(l, r));
    _init(_rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  void _update(data_type k, int P, int p, int l, int r) {
    if (l == r) {
      data[p] = {k, k * k % MOD};
      return;
    }
    if (P <= _mid(l, r)) _update(k, P, _lch(p), l, _mid(l, r));
    if (P > _mid(l, r)) _update(k, P, _rch(p), _mid(l, r) + 1, r);
    _push_up(p);
  }
  data_type _query(int L, int R, int type, int p, int l, int r) {
    if (L <= l && r <= R) return type == 2 ? data[p].a : data[p].a_sqr;
    data_type res = 0;
    if (L <= _mid(l, r))
      (res += _query(L, R, type, _lch(p), l, _mid(l, r))) %= MOD;
    if (R > _mid(l, r))
      (res += _query(L, R, type, _rch(p), _mid(l, r) + 1, r)) %= MOD;
    return res;
  }

public:
  void init(int n) { _init(1, 1, this->n = n); }
  void update(data_type k, int P) { _update(k, P, 1, 1, n); }
  data_type query(int L, int R, int type) {
    return _query(L, R, type, 1, 1, n);
  }
};
Segtree<N> tr;
i64 inv(i64 a) {
  i64 res(1), b(MOD - 2);
  for (; b; b >>= 1, (a *= a) %= MOD)
    if (b & 1) (res *= a) %= MOD;
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cout << fixed << setprecision(4);
  tr.init(n);
  i64 op, l, r;
  while (m--) {
    cin >> op >> l >> r;
    switch (op) {
      case 1: tr.update(r, l); break;
      case 2:
        i64 x = tr.query(l, r, 3) * inv(r - l + 1) % MOD,
            y = tr.query(l, r, 2) * inv(r - l + 1) % MOD;
        cout << (x + MOD - y * y % MOD) % MOD << '\n';
        break;
    }
  }
  return 0;
}
