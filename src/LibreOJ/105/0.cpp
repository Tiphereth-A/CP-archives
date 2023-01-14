#include <bits/stdc++.h>
template <class Tp>
class TreapNR {
  static_assert(!std::is_unsigned<Tp>::value, "Tp should not be unsigned");
  using self = TreapNR<Tp>;

protected:
  struct Node {
    Node *l, *r;
    uint_fast64_t rid;
    size_t cnt, sz;
    Tp val;
    bool flp = false;
    Node(uint_fast64_t rid, Tp val)
      : l(nullptr), r(nullptr), rid(rid), cnt(1), sz(1), val(val) {}
    explicit Node(Node *rhs)
      : rid(rhs->rid), cnt(rhs->cnt), sz(rhs->sz), val(rhs->val) {}
    friend std::ostream &operator<<(std::ostream &os, Node &ptr) {
      ptr.flip();
      if (ptr.l != nullptr) os << *(ptr.l);
      os << ptr.val << ' ';
      if (ptr.r != nullptr) os << *(ptr.r);
      return os;
    }
    constexpr void update() {
      sz = cnt;
      if (l != nullptr) sz += l->sz;
      if (r != nullptr) sz += r->sz;
    }

  protected:
    void flip_() {
      std::swap(l, r);
      if (l != nullptr) l->flp ^= 1;
      if (r != nullptr) r->flp ^= 1;
      flp = false;
    }

  public:
    void flip() {
      if (flp) flip_();
    }
  };
  std::pair<Node *, Node *> split(Node *cur, size_t sz) {
    if (cur == nullptr) return {nullptr, nullptr};
    cur->flip();
    size_t lsz = cur->l == nullptr ? 0 : cur->l->sz;
    if (lsz < sz) {
      auto &&_ = split(cur->r, sz - lsz - 1);
      cur->r = _.first;
      cur->update();
      return {cur, _.second};
    } else {
      auto &&_ = split(cur->l, sz);
      cur->l = _.second;
      cur->update();
      return {_.first, cur};
    }
  }
  Node *merge(Node *u, Node *v) {
    if (u == nullptr && v == nullptr) return nullptr;
    if (u != nullptr && v == nullptr) return u;
    if (v != nullptr && u == nullptr) return v;
    u->flip();
    v->flip();
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
  friend std::ostream &operator<<(std::ostream &os, self &tree) {
    if (tree.root == nullptr) return os << '\n';
    return (os << *(tree.root)).seekp(-1, std::ios_base::end) << '\n';
  }
  void insert(Tp const &val) {
    auto &&_ = split(root, val);
    auto &&_1 = split(_.first, val - 1);
    Node *new_node;
    if (_1.second == nullptr) new_node = new Node(key_eng_(), val);
    else {
      _1.second->cnt++;
      _1.second->update();
    }
    root = merge(merge(_1.first, _1.second == nullptr ? new_node : _1.second),
                 _.second);
  }
  void reverse(size_t l, size_t r) {
    assert(0 < l && l <= r);
    auto &&tl = split(root, l - 1);
    auto &&tr = split(tl.second, r - l + 1);
    tr.first->flp = true;
    root = merge(tl.first, merge(tr.first, tr.second));
  }
};
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  TreapNR<int> tr;
  for (int i = 1; i <= n; ++i) tr.insert(i);
  for (int x, y; m; --m) {
    cin >> x >> y;
    tr.reverse(x, y);
  }
  cout << tr;
  return 0;
}
