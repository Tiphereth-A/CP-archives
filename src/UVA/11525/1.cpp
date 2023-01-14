#include <bits/stdc++.h>
namespace tifa_libs {
using u32 = uint32_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
namespace tifa_libs::ds {
class weighted_segtree {
  const size_t n;
  vec<size_t> t;
  void ins_(size_t x, size_t l, size_t r, size_t pos) {
    if (l == r) return void(++t[x]);
    size_t mid = l + (r - l) / 2;
    if (pos <= mid) ins_(x << 1, l, mid, pos);
    else ins_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  void del_(size_t x, size_t l, size_t r, size_t pos) {
    if (l == r) return void(--t[x]);
    size_t mid = l + (r - l) / 2;
    if (pos <= mid) del_(x << 1, l, mid, pos);
    else del_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  size_t kth_min_(size_t x, size_t l, size_t r, size_t k) const {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2;
    if (k <= t[x << 1]) return kth_min_(x << 1, l, mid, k);
    return kth_min_(x << 1 | 1, mid + 1, r, k - t[x << 1]);
  }
  size_t kth_max_(size_t x, size_t l, size_t r, size_t k) const {
    if (l == r) return l;
    size_t mid = l + (r - l) / 2;
    if (k <= t[x << 1 | 1]) return kth_min_(x << 1 | 1, mid + 1, r, k);
    return kth_min_(x << 1, l, mid, k - t[x << 1 | 1]);
  }
  size_t frequency_(size_t x, size_t l, size_t r, size_t k) const {
    if (l == r) return t[x];
    else {
      size_t mid = l + (r - l) / 2;
      if (k <= mid) return frequency_(x << 1, l, mid, k);
      return frequency_(x << 1 | 1, mid + 1, r, k);
    }
  }
  size_t frequency_(size_t x, size_t l, size_t r, size_t L, size_t R) const {
    if (l == r) return t[x];
    else {
      size_t mid = l + (r - l) / 2, ret = size_t(0);
      if (L <= mid) ret = frequency_(x << 1, l, mid, L, R);
      if (R > mid) ret += frequency_(x << 1 | 1, mid + 1, r, L, R);
      return ret;
    }
  }

public:
  explicit weighted_segtree(size_t N): n(N), t(N * 4) {}
  void ins(size_t pos) { ins_(1, 0, n - 1, pos); }
  void del(size_t pos) { del_(1, 0, n - 1, pos); }
  size_t kth_min(size_t k) { return kth_min_(1, 0, n - 1, k); }
  size_t kth_max(size_t k) { return kth_max_(1, 0, n - 1, k); }
  size_t frequency(size_t k) { return frequency_(1, 0, n - 1, k); }
  size_t frequency(size_t l, size_t r) { return frequency_(1, 0, n - 1, l, r); }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::math {
vec<u32> cantor_inv_seq(vec<u32> const &s) {
  size_t n = s.size();
  ds::weighted_segtree tr(n + 1);
  for (size_t i = 1; i <= n; ++i) tr.ins(i);
  vec<u32> p(n);
  for (size_t i = 0; i < n; ++i) tr.del(p[i] = (u32)tr.kth_min(s[i] + 1));
  return p;
}
}  // namespace tifa_libs::math
void solve() {
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  for (auto &i : a) std::cin >> i;
  auto p = tifa_libs::math::cantor_inv_seq(a);
  for (size_t i = 0; i < n; ++i) std::cout << p[i] << " \n"[i == n - 1];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
