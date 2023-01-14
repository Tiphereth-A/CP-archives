#include <cassert>
#include <cstdint>
#include <functional>
using std::size_t;
template <typename key_t, typename compare_t = std::less<key_t>>
struct rb_tree {
  struct node_t {
    node_t *fa;
    node_t *ch[2];
    key_t data;
    size_t sz;
    bool red;
    auto child_dir() const -> bool { return this == fa->ch[1]; }
  };
  using pointer = node_t *;
  using const_pointer = const node_t *;
  using pointer_const = node_t * const;
  const compare_t compare;
  pointer root;
  rb_tree(): compare{}, root{nullptr} {}
  ~rb_tree() {
    post_order([](auto it) { delete it; });
  }
  auto size() const -> size_t { return size(root); }
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
  auto order_of_key(const key_t &key) const -> size_t {
    size_t ans = 0;
    auto now = root;
    while (now) {
      if (!compare(now->data, key)) now = now->ch[0];
      else ans += size(now->ch[0]) + 1, now = now->ch[1];
    }
    return ans;
  }
  auto find_by_order(size_t order) const -> const_pointer {
    const_pointer now = root, ans = nullptr;
    while (now && now->sz >= order) {
      auto lsize = size(now->ch[0]);
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
    pointer n = new node_t;
    n->fa = n->ch[0] = n->ch[1] = nullptr;
    n->data = data, n->sz = 1;
    pointer now = root, p = nullptr;
    bool dir = 0;
    while (now) {
      p = now;
      dir = compare(now->data, data);
      now = now->ch[dir];
    }
    insert_fixup_leaf(p, n, dir);
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
    pointer result;
    if (p->ch[0] && p->ch[1]) {
      auto s = leftmost(p->ch[1]);
      std::swap(s->data, p->data);
      result = p, p = s;
    } else result = next(p);
    erase_fixup_branch_or_leaf(p);
    delete p;
    return result;
  }

private:
  static auto size(const_pointer p) -> size_t { return p ? p->sz : 0; }
  static auto is_red(const_pointer p) -> bool { return p ? p->red : false; }
  auto most(const_pointer p, bool dir) const -> pointer {
    if (!p) return nullptr;
    while (p->ch[dir]) p = p->ch[dir];
    return (pointer)p;
  }
  auto neighbour(const_pointer p, bool dir) const -> pointer {
    if (!p) return nullptr;
    if (p->ch[dir]) return most(p->ch[dir], !dir);
    if (p == root) return nullptr;
    while (p && p->fa && p->child_dir() == dir) p = p->fa;
    return p ? p->fa : nullptr;
  }
  void insert_leaf(pointer_const p, pointer_const n, bool dir) {
    if (!p) {
      root = n;
      return;
    }
    p->ch[dir] = n, n->fa = p;
    auto now = p;
    while (now) now->sz++, now = now->fa;
  }
  void erase_branch_or_leaf(pointer_const n) {
    auto p = n->fa, s = n->ch[0] ? n->ch[0] : n->ch[1];
    if (s) s->fa = p;
    if (!p) {
      root = s;
      return;
    }
    p->ch[n->child_dir()] = s;
    auto now = p;
    while (now) now->sz--, now = now->fa;
  }
  auto rotate(pointer p, bool dir) -> pointer {
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
    return s;
  }
  void insert_fixup_leaf(pointer p, pointer n, bool dir) {
    n->red = p;
    insert_leaf(p, n, dir);
    while (is_red(p = n->fa)) {
      bool p_dir = p->child_dir();
      auto g = p->fa, u = g->ch[!p_dir];
      if (is_red(u)) {
        p->red = u->red = false;
        g->red = true;
        n = g;
        continue;
      }
      if (n->child_dir() != p_dir) rotate(p, p_dir), std::swap(n, p);
      p->red = false, g->red = true;
      rotate(g, !p_dir);
    }
    root->red = false;
  }
  void erase_fixup_branch_or_leaf(pointer n) {
    bool n_dir = n == root ? false : n->child_dir();
    erase_branch_or_leaf(n);
    auto p = n->fa;
    if (!p) {
      if (root) root->red = false;
      return;
    } else {
      auto s = p->ch[n_dir];
      if (s) {
        s->red = false;
        return;
      }
    }
    while (p && !n->red) {
      auto s = p->ch[!n_dir];
      if (is_red(s)) {
        s->red = false, p->red = true;
        rotate(p, n_dir);
        s = p->ch[!n_dir];
      }
      auto c = s->ch[n_dir], d = s->ch[!n_dir];
      if (!is_red(c) && !is_red(d)) {
        s->red = true;
        n = p;
        goto end_erase_fixup;
      }
      if (!is_red(d)) {
        c->red = false, s->red = true;
        rotate(s, !n_dir);
        s = p->ch[!n_dir], c = s->ch[n_dir], d = s->ch[!n_dir];
      }
      s->red = p->red, p->red = d->red = false;
      rotate(p, n_dir), n = root;
    end_erase_fixup:
      p = n->fa;
      if (!p) break;
      n_dir = n->child_dir();
    }
    n->red = false;
  }
};
#include <iostream>
#include <numeric>
#include <vector>
template <bool P6136>
struct IO_luogu_P3369_P6136 {
  int last_ans = 0;
  size_t n, m;
  std::vector<int> a;
  std::vector<int> ans_list;
  void init() {
    std::cin >> n;
    if (!P6136) {
      m = n;
      return;
    }
    std::cin >> m;
    a.resize(n);
    for (auto &i : a) std::cin >> i;
  }
  int opt() {
    int x;
    std::cin >> x;
    return x;
  }
  int x() {
    int x;
    std::cin >> x;
    return P6136 ? x ^ last_ans : x;
  }
  void print(int ans) { ans_list.push_back(last_ans = ans); }
  void print_total_ans() {
    if (P6136)
      std::cout << std::accumulate(
                     ans_list.begin(), ans_list.end(), 0, std::bit_xor<int>{})
                << '\n';
    else
      for (auto &&i : ans_list) std::cout << i << '\n';
  }
};
IO_luogu_P3369_P6136<false> io;
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  io.init();
  size_t n = io.n, m = io.m;
  rb_tree<std::pair<int, int>> bt;
  int cnt = 0;
  for (auto i : io.a) bt.insert(std::make_pair(i, cnt++));
  for (int i = 0, opt, x; (size_t)i < m; ++i) {
    opt = io.opt(), x = io.x();
    switch (opt) {
      case 1: bt.insert({x, cnt++}); break;
      case 2: bt.erase(bt.lower_bound({x, 0})); break;
      case 3: io.print((int)bt.order_of_key({x, 0}) + 1); break;
      case 4: io.print(bt.find_by_order((uint32_t)x - 1)->data.first); break;
      case 6: io.print(bt.upper_bound({x, n + m})->data.first); break;
      case 5:
        auto it = bt.lower_bound({x, 0});
        io.print((it ? bt.prev(it) : bt.rightmost(bt.root))->data.first);
        break;
    }
  }
  io.print_total_ans();
  return 0;
}
