#include <bits/stdc++.h>
template <class Tp>
class TreapNR {
  using self = TreapNR<Tp>;

protected:
  struct Node {
    Node *l, *r;
    uint_fast64_t rid;
    size_t cnt, sz;
    Tp val;
    Node(uint_fast64_t rid, Tp val)
      : l(nullptr), r(nullptr), rid(rid), cnt(1), sz(1), val(val) {}
    explicit Node(Node *rhs)
      : rid(rhs->rid), cnt(rhs->cnt), sz(rhs->sz), val(rhs->val) {}
    constexpr void update() {
      sz = cnt;
      if (l != nullptr) sz += l->sz;
      if (r != nullptr) sz += r->sz;
    }
  };
  std::pair<Node *, Node *> split(Node *cur, Tp const &val) {
    if (cur == nullptr) return {nullptr, nullptr};
    if (val < cur->val) {
      auto _ = split(cur->l, val);
      cur->l = _.second;
      cur->update();
      return {_.first, cur};
    } else {
      auto _ = split(cur->r, val);
      cur->r = _.first;
      cur->update();
      return {cur, _.second};
    }
  }
  std::tuple<Node *, Node *, Node *> split_by_rk(Node *cur, size_t rk) {
    if (cur == nullptr) return {nullptr, nullptr, nullptr};
    size_t szl = cur->l == nullptr ? 0 : cur->l->sz;
    if (rk <= szl) {
      auto _ = split_by_rk(cur->l, rk);
      cur->l = std::get<2>(_);
      cur->update();
      return {std::get<0>(_), std::get<1>(_), cur};
    } else if (rk <= szl + cur->cnt) {
      Node *lt = cur->l, *rt = cur->r;
      cur->l = cur->r = nullptr;
      return {lt, cur, rt};
    } else {
      auto _ = split_by_rk(cur->r, rk - szl - cur->cnt);
      cur->r = std::get<0>(_);
      cur->update();
      return {cur, std::get<1>(_), std::get<2>(_)};
    }
  }
  Node *merge(Node *u, Node *v) {
    if (u == nullptr && v == nullptr) return nullptr;
    if (u != nullptr && v == nullptr) return u;
    if (v != nullptr && u == nullptr) return v;
    if (u->rid < v->rid) {
      u->r = merge(u->r, v);
      u->update();
      return u;
    } else {
      v->l = merge(u, v->l);
      v->update();
      return v;
    }
  }
  size_t rank_(Node *cur, Tp const &val) {
    auto _ = split(cur, val - 1);
    size_t ret = (_.first == nullptr ? 0 : _.first->sz) + 1;
    root = merge(_.first, _.second);
    return ret;
  }
  Tp val_(Node *cur, size_t rk) {
    auto _ = split_by_rk(cur, rk);
    Tp ret = std::get<1>(_)->val;
    root = merge(std::get<0>(_), merge(std::get<1>(_), std::get<2>(_)));
    return ret;
  }
  void copy_(Node *dst, const Node *src) {
    if (src->l != nullptr) {
      dst->l = new Node(src->l);
      copy_(dst->l, src->l);
    }
    if (src->r != nullptr) {
      if (src->r == src->l) {
        dst->r = dst->l;
        return;
      }
      dst->r = new Node(src->r);
      copy_(dst->r, src->r);
    }
  }
  void clear_(Node *now) {
    if (now == nullptr) return;
    if (now->l == now->r) now->r = nullptr;
    if (now->l != nullptr) clear_(now->l);
    if (now->r != nullptr) clear_(now->r);
    delete now;
  }
  std::mt19937_64 key_eng_;
  Node *root;

public:
  TreapNR(): key_eng_(), root(nullptr) {}
  explicit TreapNR(uint64_t seed): key_eng_(seed), root(nullptr) {}
  TreapNR(self const &rhs): key_eng_(rhs.key_eng_), root(new Node(rhs.root)) {
    copy_(root, rhs.root);
  }
  self &operator=(self const &rhs) {
    clear();
    key_eng_ = rhs.key_eng_;
    root = new Node(rhs.root);
    copy_(root, rhs.root);
    return *this;
  }
  ~TreapNR() { clear(); }
  void clear() {
    clear_(root);
    root = nullptr;
  }
  void insert(Tp const &val) {
    auto _ = split(root, val);
    auto l_tr = split(_.first, val - 1);
    Node *new_node;
    if (l_tr.second == nullptr) new_node = new Node(key_eng_(), val);
    else {
      l_tr.second->cnt++;
      l_tr.second->update();
    }
    Node *l_tr_combined =
      merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
    root = merge(l_tr_combined, _.second);
  }
  void erase(Tp const &val) {
    auto _ = split(root, val);
    auto l_tr = split(_.first, val - 1);
    if (l_tr.second->cnt > 1) {
      l_tr.second->cnt--;
      l_tr.second->update();
      l_tr.first = merge(l_tr.first, l_tr.second);
    } else {
      if (_.first == l_tr.second) _.first = nullptr;
      delete l_tr.second;
      l_tr.second = nullptr;
    }
    root = merge(l_tr.first, _.second);
  }
  size_t rank(Tp const &val) { return rank_(root, val); }
  Tp val(size_t rk) {
    assert(rk > 0);
    return val_(root, rk);
  }
  Tp prev_val(Tp const &val) {
    auto _ = split(root, val - 1);
    Tp ret = val_(_.first, _.first->sz);
    root = merge(_.first, _.second);
    return ret;
  }
  Tp next_val(Tp const &val) {
    auto _ = split(root, val);
    Tp ret = val_(_.second, 1);
    root = merge(_.first, _.second);
    return ret;
  }
};
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  TreapNR<int> tr;
  while (t--) {
    int mode, num;
    cin >> mode >> num;
    switch (mode) {
      case 1: tr.insert(num); break;
      case 2: tr.erase(num); break;
      case 3: cout << tr.rank(num) << '\n'; break;
      case 4: cout << tr.val(num) << '\n'; break;
      case 5: cout << tr.prev_val(num) << '\n'; break;
      case 6: cout << tr.next_val(num) << '\n'; break;
    }
  }
  return 0;
}
