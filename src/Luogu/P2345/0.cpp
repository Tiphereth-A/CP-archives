#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <size_t N, typename Tp>
class BIT {
protected:
  Tp tree[N];
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() = default;
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(ptrdiff_t pos, Tp val = 1) {
    for (ptrdiff_t i = std::clamp(pos, ptrdiff_t(0), ptrdiff_t(N) - 1); i < N;
         i += lowbit(i))
      tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    for (ptrdiff_t i = std::clamp(pos, ptrdiff_t(0), ptrdiff_t(N) - 1); i;
         i = i - lowbit(i))
      ret += tree[i];
    return ret;
  }
};
BIT<50005, i64> cnt, sum;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<tuple<int, int, int>> v;
  v.reserve(n);
  for (int i = 0, x, y; i < n; ++i) {
    cin >> x >> y;
    v.emplace_back(x, y, 0);
  }
  sort(v.begin(), v.end(), [](auto const &l, auto const &r) {
    return get<1>(l) < get<1>(r);
  });
  for (int i = 0; i < n; ++i) get<2>(v[i]) = i + 1;
  for (int i = 0; i < n; ++i) cnt.modify(get<2>(v[i]));
  for (int i = 0; i < n; ++i) sum.modify(get<2>(v[i]), get<1>(v[i]));
  sort(v.begin(), v.end(), [](auto const &l, auto const &r) {
    return get<0>(l) > get<0>(r);
  });
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    ans +=
      get<0>(v[i]) *
      (sum.query(n) - sum.query(get<2>(v[i])) - sum.query(get<2>(v[i]) - 1) -
       (cnt.query(n) - cnt.query(get<2>(v[i])) - cnt.query(get<2>(v[i]) - 1)) *
         get<1>(v[i]));
    cnt.modify(get<2>(v[i]), -1);
    sum.modify(get<2>(v[i]), -get<1>(v[i]));
  }
  cout << ans;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
