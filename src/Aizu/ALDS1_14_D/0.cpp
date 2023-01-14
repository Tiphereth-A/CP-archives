#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::str {
template <typename T = std::string>
class suffixarray {
  T s;

public:
  vec<u32> sa, rk, height;
  suffixarray(T s_): s(s_), sa(s.size()), rk(s.size()) {
    u32 n = u32(s.size() - 1), m = 0, p;
    for (auto x : s_) m = std::max(m, u32(x));
    vec<u32> oldrk(n + n + 1), id(n + 1), cnt(m + 1, 0);
    for (u32 i = 1; i <= n; ++i) ++cnt[rk[i] = u32(s[i])];
    for (u32 i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (u32 i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    for (u32 w = 1;; w *= 2, m = p) {
      p = 0;
      for (u32 i = n; i > n - w; --i) id[++p] = i;
      for (u32 i = 1; i <= n; ++i)
        if (sa[i] > w) id[++p] = sa[i] - w;
      cnt = vec<u32>(m + 1, 0);
      for (u32 i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
      for (u32 i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (u32 i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
      std::copy(rk.begin(), rk.end(), oldrk.begin());
      p = 0;
      for (u32 i = 1; i <= n; ++i) {
        u32 x = sa[i], y = sa[i - 1];
        rk[x] = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w] ? p : ++p;
      }
      if (p == n) break;
    }
  }
  void get_height() {
    u32 n = s.size() - 1;
    vec<u32> height(n + 1);
    for (u32 i = 1, k = 0; i <= n; ++i) {
      if (rk[i] == 1) continue;
      if (k) --k;
      while (i + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
      height[rk[i]] = k;
    }
  }
  i32 compare_substr(T t, u32 begs = 1, u32 begt = 1) {
    while (begs < s.size() && begt < t.size()) {
      if (t[begt] > s[begs]) return -1;
      if (t[begt] < s[begs]) return 2;
      ++begs, ++begt;
    }
    return begs == s.size() && begt == t.size() ? 0 :
                                                  (begt >= t.size() ? 1 : -1);
  }
  u32 lower_bound(T t) {
    u32 l = 1, r = u32(s.size() - 1), ret = u32(s.size());
    while (r >= l) {
      u32 mid = l + (r - l) / 2;
      if (compare_substr(t, sa[mid]) < 0) l = mid + 1;
      else r = mid - 1, ret = mid;
    }
    return ret;
  }
  u32 upper_bound(T t) {
    u32 l = 1, r = u32(s.size() - 1), ret = u32(s.size());
    while (r >= l) {
      u32 mid = l + (r - l) / 2;
      if (compare_substr(t, sa[mid]) <= 1) l = mid + 1;
      else r = mid - 1, ret = mid;
    }
    return ret;
  }
  u32 frequency(T t) { return upper_bound(t) - lower_bound(t); }
};
}  // namespace tifa_libs::str
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string t, s;
  std::cin >> t;
  t = " " + t;
  u32 n;
  std::cin >> n;
  tifa_libs::str::suffixarray sa(t);
  for (u32 i = 0; i < n; ++i) {
    std::cin >> s;
    s = " " + s;
    std::cout << bool(sa.frequency(s)) << '\n';
  }
  return 0;
}
