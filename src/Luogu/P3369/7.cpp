#include <bits/extc++.h>
using tree_size_t = uint32_t;
class bst_tag {
protected:
  template <typename pointer>
  auto size(pointer p) const -> tree_size_t {
    return p ? p->sz : 0;
  }
  template <typename pointer>
  void insert_leaf(pointer &root, pointer p, pointer n, bool dir) {
    if (!p) {
      root = n;
      return;
    }
    p->ch[dir] = n, n->fa = p;
    auto now = p;
    while (now) now->sz++, now = now->fa;
  }
  template <typename pointer>
  void erase_branch_leaf(pointer &root, pointer n) {
    auto p = n->fa, s = n->ch[0] ? n->ch[0] : n->ch[1];
    if (!p) {
      root = s;
      if (s) s->fa = nullptr;
      return;
    }
    if (p) p->ch[n->child_dir()] = s;
    if (s) s->fa = p;
    auto now = p;
    while (now) now->sz--, now = now->fa;
  }
  template <typename pointer>
  void rotate(pointer &root, pointer p, bool dir) {
    auto g = p->fa;
    auto s = p->ch[!dir];
    assert(s);
    s->sz = p->sz, p->sz = size(p->ch[dir]) + size(s->ch[dir]) + 1;
    auto c = s->ch[dir];
    if (c) c->fa = p;
    p->ch[!dir] = c, s->ch[dir] = p;
    p->fa = s, s->fa = g;
    if (g) g->ch[p == g->ch[1]] = s;
    else root = s;
  }
};
class rbt_tag: protected bst_tag {
protected:
  template <typename pointer>
  auto is_red(pointer p) const -> bool {
    return p ? p->red : false;
  }
  template <typename pointer>
  void insert_leaf(pointer &root, pointer p, pointer n, bool dir) {
    n->red = p;
    bst_tag::insert_leaf(root, p, n, dir);
    while (is_red(p = n->fa)) {
      bool p_dir = p->child_dir();
      auto g = p->fa, u = g->ch[!p_dir];
      if (is_red(u)) {
        p->red = u->red = false;
        g->red = true;
        n = g;
        continue;
      }
      if (n->child_dir() != p_dir) rotate(root, p, p_dir), swap(n, p);
      p->red = false, g->red = true;
      rotate(root, g, !p_dir);
    }
    root->red = false;
  }
  template <typename pointer>
  void erase_branch_leaf(pointer &root, pointer n) {
    if (n == root) {
      bst_tag::erase_branch_leaf(root, n);
      if (root) root->red = false;
      return;
    }
    bool n_dir = n->child_dir();
    bst_tag::erase_branch_leaf(root, n);
    if (n->red) return;
    auto p = n->fa;
    if (p) {
      auto s = p->ch[n_dir];
      if (s) s->red = false;
      return;
    }
    while ((p = n->fa) && p && !n->red) {
      n_dir = n->child_dir();
      auto b = p->ch[!n_dir];
      if (is_red(b)) {
        b->red = false, p->red = true;
        rotate(root, p, n_dir);
        b = p->ch[!n_dir];
      }
      auto c = b->ch[n_dir], d = b->ch[!n_dir];
      if (!is_red(c) && !is_red(d)) {
        b->red = true;
        n = p;
        continue;
      }
      if (!is_red(d)) {
        c->red = false, b->red = true;
        rotate(root, b, !n_dir);
        b = c, c = b->ch[n_dir], d = b->ch[!n_dir];
      }
      b->red = p->red, p->red = d->red = false;
      rotate(root, p, n_dir);
      break;
    }
  }
};
template <typename T, typename data_t>
struct balance_tree_node_t {};
template <typename data_t>
struct balance_tree_node_t<bst_tag, data_t> {
  balance_tree_node_t *fa;
  balance_tree_node_t *ch[2];
  data_t data;
  tree_size_t sz;
  auto child_dir() const -> bool { return this == fa->ch[1]; }
};
template <typename data_t>
struct balance_tree_node_t<rbt_tag, data_t> {
  balance_tree_node_t *fa;
  balance_tree_node_t *ch[2];
  data_t data;
  tree_size_t sz;
  bool red;
  auto child_dir() const -> bool { return this == fa->ch[1]; }
};
template <typename key_t,
          typename tree_tag_t,
          typename compare_t = std::less<key_t>,
          template <typename> typename allocator_t = std::allocator>
struct balance_tree: public tree_tag_t {
  using node_t = balance_tree_node_t<tree_tag_t, key_t>;
  using pointer = node_t *;
  using const_pointer = const node_t *;
  static constexpr compare_t compare{};
  allocator_t<node_t> alloc;
  pointer root;
  balance_tree(): tree_tag_t(), root{nullptr} {}
  ~balance_tree() {
    post_order([this](auto it) { alloc.deallocate(it, 1); });
  }
  auto size() const -> tree_size_t { return tree_tag_t::size(root); }
  template <typename F>
  void pre_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      callback(p), f(f, p->ch[0]), f(f, p->ch[1]);
    };
    f(f, root);
  }
  template <typename F>
  void in_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      f(f, p->ch[0]), callback(p), f(f, p->ch[1]);
    };
    f(f, root);
  }
  template <typename F>
  void post_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      f(f, p->ch[0]), f(f, p->ch[1]), callback(p);
    };
    f(f, root);
  }
  auto leftmost(const_pointer p) const { return most(p, 0); }
  auto rightmost(const_pointer p) const { return most(p, 1); }
  auto prev(const_pointer p) const { return neighbour(p, 0); }
  auto next(const_pointer p) const { return neighbour(p, 1); }
  auto lower_bound(const key_t &key) const -> pointer {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (!compare(now->data, key)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  auto upper_bound(const key_t &key) const -> pointer {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (compare(key, now->data)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  auto order_of_key(const key_t &key) const -> tree_size_t {
    tree_size_t ans = 0;
    auto now = root;
    while (now) {
      if (!compare(now->data, key)) now = now->ch[0];
      else ans += tree_tag_t::size(now->ch[0]) + 1, now = now->ch[1];
    }
    return ans;
  }
  auto find_by_order(tree_size_t order) const -> const_pointer {
    const_pointer now = root, ans = nullptr;
    while (now && now->sz >= order) {
      auto lsize = tree_tag_t::size(now->ch[0]);
      if (order < lsize) now = now->ch[0];
      else {
        ans = now;
        if (order == lsize) break;
        now = now->ch[1], order -= lsize + 1;
      }
    }
    return ans;
  }
  auto insert(const key_t &data) -> const_pointer {
    pointer n = alloc.allocate(1);
    n->fa = n->ch[0] = n->ch[1] = nullptr;
    n->data = data, n->sz = 1;
    pointer now = root, p = nullptr;
    bool dir = 0;
    while (now) {
      p = now;
      dir = compare(now->data, data);
      now = now->ch[dir];
    }
    tree_tag_t::insert_leaf(root, p, n, dir);
    return n;
  }
  auto erase(const key_t &key) -> bool {
    auto p = lower_bound(key);
    if (!p || p->data != key) return false;
    erase(p);
    return true;
  }
  auto erase(pointer p) -> const_pointer {
    if (!p) return nullptr;
    if (p->ch[0] && p->ch[1]) {
      auto s = rightmost(p->ch[0]);
      swap(s->data, p->data);
      p = s;
    }
    auto result = next(p);
    tree_tag_t::erase_branch_leaf(root, p);
    alloc.deallocate(p, 1);
    return result;
  }

private:
  auto most(const_pointer p, bool dir) const -> pointer {
    if (!p) return nullptr;
    while (p->ch[dir]) p = p->ch[dir];
    return (pointer)p;
  }
  auto neighbour(const_pointer p, bool dir) const -> pointer {
    if (!p) return nullptr;
    if (p->ch[dir]) return most(p->ch[dir], !dir);
    if (p == root) return nullptr;
    while (p && p->fa && !p->child_dir()) p = p->fa;
    return p ? p->fa : nullptr;
  }
};
std::vector<int> data;
auto solve2() {
  size_t idx = 0, n = (size_t)data[idx++];
  balance_tree<std::pair<int, int>, rbt_tag> bt;
  std::vector<int> result;
  result.reserve(n);
  for (int i = 0, opt, x; (size_t)i < n; ++i) {
    opt = data[idx++];
    x = data[idx++];
    switch (opt) {
      case 1: bt.insert({x, i}); break;
      case 2: bt.erase(bt.lower_bound({x, 0})); break;
      case 3: result.push_back((int)bt.order_of_key({x, 0}) + 1); break;
      case 4:
        result.push_back(bt.find_by_order((uint32_t)x - 1)->data.first);
        break;
      case 6: result.push_back(bt.upper_bound({x, n})->data.first); break;
      case 5:
        auto it = bt.lower_bound({x, 0});
        result.push_back(
          (it ? bt.prev(it) : bt.rightmost(bt.root))->data.first);
        break;
    }
  }
  return result;
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  size_t n;
  std::cin >> n;
  data.resize(n * 2 + 1);
  data[0] = (int)n;
  for (size_t i = 1; i < data.size(); i += 2)
    std::cin >> data[i] >> data[i + 1];
  auto result = solve2();
  for (auto &&i : result) std::cout << i << '\n';
  std::cout.flush();
  return 0;
}
