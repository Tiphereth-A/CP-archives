#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
template <typename Tp>
class persistable_seg_tree {
  static const size_t MRATE = 24;
  using self = persistable_seg_tree<Tp>;
  using data_t = Tp;
  using index_t = size_t;

protected:
  struct node_t {
    data_t data;
    index_t l, r;
    node_t(data_t const &data_ = data_t(0), index_t l_ = 0, index_t r_ = 0)
      : data(data_), l(l_), r(r_) {}
  };
  index_t data_sz;
  std::vector<node_t> nodes;
  std::vector<index_t> roots;
  void _init(index_t const &l,
             index_t const &r,
             std::vector<data_t> const &a,
             index_t &now) {
    now = nodes.size();
    nodes.emplace_back(data_t(0), nodes.size(), nodes.size());
    if (l == r) {
      nodes[now].data = a[l];
      return;
    }
    index_t mid = l + ((r - l) >> 1);
    _init(l, mid, a, nodes[now].l);
    _init(mid + 1, r, a, nodes[now].r);
  }
  void _modify(index_t const &l,
               index_t const &r,
               index_t &now,
               index_t const &pre,
               index_t const &pos,
               data_t const &k) {
    now = nodes.size();
    nodes.push_back(nodes[pre]);
    if (l == r) {
      nodes[now].data = k;
      return;
    }
    index_t mid = l + ((r - l) >> 1);
    if (pos <= mid) _modify(l, mid, nodes[now].l, nodes[pre].l, pos, k);
    else _modify(mid + 1, r, nodes[now].r, nodes[pre].r, pos, k);
  }
  data_t const &_query(index_t const &now,
                       index_t const &l,
                       index_t const &r,
                       index_t const &pos) const {
    if (l == r) return nodes[now].data;
    index_t mid = l + ((r - l) >> 1);
    if (pos <= mid) return _query(nodes[now].l, l, mid, pos);
    else return _query(nodes[now].r, mid + 1, r, pos);
  }

public:
  constexpr explicit persistable_seg_tree(index_t const &_size)
    : data_sz(_size), nodes(1), roots(1) {
    nodes.reserve(data_sz * MRATE);
  }
  explicit persistable_seg_tree(std::vector<data_t> const &data_array)
    : persistable_seg_tree(data_array.size() - 1) {
    _init(1, data_sz, data_array, roots.back());
  }
  self &clear() {
    nodes.clear();
    roots.clear();
    return *this;
  }
  constexpr index_t data_size() const { return this->data_sz; }
  constexpr index_t node_size() const { return nodes.size(); }
  constexpr index_t version_size() const { return roots.size(); }
  self &modify(index_t const &version, index_t const &pos, data_t const &data) {
    roots.push_back(0);
    _modify(1, data_sz, roots.back(), roots[version], pos, data);
    return *this;
  }
  data_t const &query(index_t const &version, index_t const &pos) {
    roots.push_back(roots[version]);
    return _query(roots[version], 1, data_sz, pos);
  }
  size_t memory_used() const {
    return sizeof(nodes[0]) * nodes.capacity() +
           sizeof(roots[0]) * roots.capacity();
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1);
  for_(i, 1, n) cin >> a[i];
  persistable_seg_tree<int> pst(a);
  for_(i, 1, m, v, id, loc, val) {
    cin >> v >> id >> loc;
    if (id == 1) {
      cin >> val;
      pst.modify(v, loc, val);
    } else cout << pst.query(v, loc) << '\n';
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
