#include <bits/stdc++.h>
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
using vecu = vec<u32>;
using vvecu = vvec<u32>;
using vecb = vec<bool>;
#undef assert
#define assert(x) 42
using namespace std::literals;
constexpr i8 operator""_i8(unsigned long long x) { return (i8)x; }
constexpr i16 operator""_i16(unsigned long long x) { return (i16)x; }
constexpr i32 operator""_i32(unsigned long long x) { return (i32)x; }
constexpr i64 operator""_i64(unsigned long long x) { return (i64)x; }
constexpr isz operator""_iz(unsigned long long x) { return (isz)x; }
constexpr u8 operator""_u8(unsigned long long x) { return (u8)x; }
constexpr u16 operator""_u16(unsigned long long x) { return (u16)x; }
constexpr u32 operator""_u32(unsigned long long x) { return (u32)x; }
constexpr u64 operator""_u64(unsigned long long x) { return (u64)x; }
constexpr usz operator""_uz(unsigned long long x) { return (usz)x; }
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using value_type = vvecu;
  value_type g;
  u32 cnt_arc;
  vecu deg_in;
  explicit constexpr alist(u32 n = 0): g(n), cnt_arc(0), deg_in(0) {
    if constexpr (with_deg) deg_in.resize(n);
  }
  constexpr void add_arc(u32 u, u32 v) {
    g[u].push_back(v), ++cnt_arc;
    if constexpr (with_deg) ++deg_in[v];
  }
};
template <class G>
concept is_alist =
  (std::is_base_of_v<alist<true>, G> || std::is_base_of_v<alist<false>, G>);
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <bool with_deg = false>
class chordal {
  alist<with_deg> const &g;
  vecu deg;

public:
  vecu peo, rnk;
  explicit constexpr chordal(alist<with_deg> const &g)
    : g(g), deg(g.g.size()), peo(g.g.size()), rnk(g.g.size()) {
    for (auto &i : g.g) assert(std::ranges::is_sorted(i));
    u32 n = (u32)g.g.size();
    vecu l(n * 2 + 1), r, idx(n);
    std::iota(l.begin(), l.end(), 0);
    r = l;
    auto ins = [&](u32 i, u32 j) { r[l[i] = l[j]] = i, r[l[j] = i] = j; };
    auto del = [&](u32 i) { r[l[i]] = r[i], l[r[i]] = l[i]; };
    for (u32 i = 0; i < n; ++i) ins(i, n);
    u32 li = n;
    for (u32 i = 0; i < n; ++i) {
      ++li;
      while (l[li] == li) --li;
      u32 v = l[li];
      idx[v] = -1_u32, del(v);
      for (u32 to : g.g[v])
        if (~idx[to]) ++deg[to], del(to), ins(to, n + (++idx[to]));
      peo[i] = v;
    }
    std::ranges::reverse(peo);
    for (u32 i = 0; i < n; ++i) rnk[peo[i]] = i;
  }
  template <bool find_indcycle = false>
  std::conditional_t<find_indcycle, std::optional<vecu>, bool>
  is_chordal_graph() const {
    for (u32 u : peo) {
      vecu s;
      s.reserve(g.g[u].size());
      for (auto v : g.g[u])
        if (rnk[u] < rnk[v]) {
          s.push_back(v);
          if (rnk[s.back()] < rnk[s[0]]) std::swap(s[0], s.back());
        }
      for (u32 j = 1; j < s.size(); ++j)
        if (!std::ranges::binary_search(g.g[s[0]], s[j])) {
          if constexpr (!find_indcycle) return false;
          else {
            u32 x = s[j], y = s[0], z = u;
            vecu pre(peo.size(), -1_u32);
            std::queue<u32> q({x});
            while (!q.empty()) {
              u32 t = q.front();
              q.pop();
              if (std::ranges::binary_search(g.g[t], y)) {
                pre[y] = t;
                vecu path = {y};
                while (path.back() != x) path.push_back(pre[path.back()]);
                path.push_back(z);
                return path;
              }
              for (u32 u : g.g[t])
                if (u != z && !std::ranges::binary_search(g.g[u], z) &&
                    !~pre[u])
                  pre[u] = t, q.push(u);
            }
          }
        }
    }
    if constexpr (find_indcycle) return {};
    else return true;
  }
  constexpr vecu maximal_cliques() const {
    vecu fst(peo.size(), -1_u32), n(peo.size()), res;
    vecb vis(peo.size());
    for (u32 u : peo)
      for (auto v : g.g[u])
        if (rnk[u] < rnk[v]) {
          ++n[u];
          if (!~fst[u] || rnk[v] < rnk[fst[u]]) fst[u] = v;
        }
    for (u32 u : peo) {
      if (vis[u]) continue;
      res.push_back(u);
      vis[fst[u]] = n[u] > n[fst[u]];
    }
    return res;
  }
  constexpr u32 chromatic_number() const {
    return *std::ranges::max_element(deg) + 1;
  }
  constexpr vecu max_independent_set() const {
    vecu res;
    vecb vis(peo.size());
    for (u32 u : peo) {
      if (vis[u]) continue;
      res.push_back(u);
      for (u32 v : g.g[u]) vis[v] = true;
    }
    return res;
  }
};
}  // namespace tifa_libs::graph
void solve([[maybe_unused]] int t_ = 0) {
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist<> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u;
    --v;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  for (auto &i : g.g) std::ranges::sort(i);
  tifa_libs::graph::chordal<> chd(g);
  std::cout << chd.max_independent_set().size() << '\n';
}
using namespace std;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cerr << fixed << setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
