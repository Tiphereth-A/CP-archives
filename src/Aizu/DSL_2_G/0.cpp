#include <bits/stdc++.h>
using i64 = int64_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::ds {
template <class T, class F>
class segtree_old {
  struct YYZ {
    T w, sign, sign1, _min, _max;
  };
  vec<YYZ> t;
  void pushup(usz x) {
    t[x].w = t[x << 1].w + t[x << 1 | 1].w;
    t[x]._min = std::min(t[x << 1]._min, t[x << 1 | 1]._min);
    t[x]._max = std::max(t[x << 1]._max, t[x << 1 | 1]._max);
  }
  void build(vec<T> const &a, usz x, usz l, usz r) {
    t[x].sign1 = 1;
    if (l == r) return void(t[x].w = a[l]);
    usz mid = l + (r - l) / 2;
    build(a, x << 1, l, mid), build(a, x << 1 | 1, mid + 1, r);
    pushup(x);
  }
  void pushdown(usz x, usz l, usz r) {
    if (t[x].sign1 != 1) {
      t[x << 1].w *= t[x].sign1;
      t[x << 1].sign *= t[x].sign1, t[x << 1].sign1 *= t[x].sign1;
      t[x << 1]._min *= t[x].sign1, t[x << 1]._max *= t[x].sign1;
      t[x << 1 | 1].w *= t[x].sign1;
      t[x << 1 | 1].sign *= t[x].sign1, t[x << 1 | 1].sign1 *= t[x].sign1;
      t[x << 1 | 1]._min *= t[x].sign1, t[x << 1 | 1]._max *= t[x].sign1;
      t[x].sign1 = 1;
    }
    if (t[x].sign) {
      usz mid = l + (r - l) / 2;
      t[x << 1].w += i64(mid - l + 1) * t[x].sign, t[x << 1].sign += t[x].sign;
      t[x << 1]._min += t[x].sign, t[x << 1]._max += t[x].sign;
      t[x << 1 | 1].w += i64(r - mid) * t[x].sign,
        t[x << 1 | 1].sign += t[x].sign;
      t[x << 1 | 1]._min += t[x].sign, t[x << 1 | 1]._max += t[x].sign;
      t[x].sign = 0;
    }
  }

public:
  explicit constexpr segtree_old(vec<T> const &a): t(a.size() * 4) {
    build(a, 1, 0, a.size() - 1);
  }
  void add(usz x, usz l, usz r, usz L, usz R, T k) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) {
      t[x].w += i64(r - l + 1) * k, t[x].sign += k;
      t[x]._min += k, t[x]._max += k;
      return;
    }
    pushdown(x, l, r);
    usz mid = l + (r - l) / 2;
    if (L <= mid) add(x << 1, l, mid, L, R, k);
    if (R > mid) add(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  void mul(usz x, usz l, usz r, usz L, usz R, T k) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) {
      t[x].w *= k;
      t[x].sign *= k, t[x].sign1 *= k;
      t[x]._min *= k, t[x]._max *= k;
      return;
    }
    pushdown(x, l, r);
    usz mid = l + (r - l) / 2;
    if (L <= mid) mul(x << 1, l, mid, L, R, k);
    if (R > mid) mul(x << 1 | 1, mid + 1, r, L, R, k);
    pushup(x);
  }
  T querys(usz x, usz l, usz r, usz L, usz R) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return t[x].w;
    pushdown(x, l, r);
    usz mid = l + (r - l) / 2;
    T ret = 0;
    if (L <= mid) ret = querys(x << 1, l, mid, L, R);
    if (R > mid) ret += querys(x << 1 | 1, mid + 1, r, L, R);
    return ret;
  }
  T querym(usz x, usz l, usz r, usz L, usz R, F f) {
    assert(R >= l && L <= r);
    if (L <= l && R >= r) return f(t[x]._min, t[x]._max);
    pushdown(x, l, r);
    usz mid = l + (r - l) / 2;
    if (L > mid) return querym(x << 1 | 1, mid + 1, r, L, R, f);
    if (R <= mid) return querym(x << 1, l, mid, L, R, f);
    return f(querym(x << 1, l, mid, L, R, f),
             querym(x << 1 | 1, mid + 1, r, L, R, f));
  }
};
}  // namespace tifa_libs::ds
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  vec<i64> a(n);
  auto min = [](i64 a, i64 b) { return std::min(a, b); };
  tifa_libs::ds::segtree_old<i64, decltype(min)> segt(a);
  for (usz i = 1; i <= q; ++i) {
    usz opt, l, r;
    std::cin >> opt >> l >> r;
    --l, --r;
    if (opt == 0) {
      i64 x;
      std::cin >> x;
      segt.add(1, 0, n - 1, l, r, x);
    } else {
      std::cout << segt.querys(1, 0, n - 1, l, r) << '\n';
    }
  }
  return 0;
}
