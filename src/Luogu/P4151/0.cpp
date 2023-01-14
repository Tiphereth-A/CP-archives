#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <std::size_t N = 64>
class XorBasis {
  using self = XorBasis<N>;
  using vector_t = std::bitset<N>;
  using iterator = vector_t *;
  using const_iterator = vector_t *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

protected:
  vector_t base[N];

public:
  constexpr XorBasis() { this->clear(); }
  constexpr XorBasis(std::initializer_list<vector_t> _list): XorBasis() {
    for (auto &&i : _list) this->insert(i);
  }
  constexpr void clear() {
    for (size_t i = 0; i < size(); ++i) base[i].reset();
  }
  constexpr size_t size() const { return N; }
  constexpr vector_t &operator[](size_t index) { return this->base[index]; }
  constexpr vector_t &operator[](size_t index) const {
    return const_cast<self * const>(this)->base[index];
  }
  constexpr iterator begin() { return this->base; }
  constexpr const_iterator begin() const {
    return const_cast<vector_t * const>(this->base);
  }
  constexpr iterator end() { return this->begin() + this->size(); }
  constexpr const_iterator end() const { return this->begin() + this->size(); }
  reverse_iterator rbegin() { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(this->end());
  }
  reverse_iterator rend() { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(this->begin());
  }
  constexpr bool insert(vector_t x) {
    bool status = false;
    for (size_t i = size() - 1; ~i; --i) {
      if (!(x[i])) continue;
      if (base[i][i]) x ^= base[i];
      else {
        for (size_t j = 0; j < i; ++j)
          if (x[j]) x ^= base[j];
        for (size_t j = i + 1; j < size(); ++j)
          if (base[j][i]) base[j] ^= x;
        base[i] = x;
        status = true;
        break;
      }
    }
    return status;
  }
  constexpr vector_t max_span() const {
    vector_t ret;
    for (const auto &i : *this) ret ^= i;
    return ret;
  }
  constexpr size_t rank() const {
    size_t res = 0;
    for (size_t i = 0; i < size(); ++i) res += base[i][i];
    return res;
  }
  constexpr std::optional<vector_t> coordinate(vector_t x) {
    vector_t res;
    for (size_t i = size() - 1; ~i; --i) {
      if (x[i] && !base[i][i]) return std::nullopt;
      if (x[i] && base[i][i]) {
        res.set(i);
        x ^= base[i];
      }
    }
    return res;
  }
};
const int N = 5e4 + 4, M = 2e5 + 5;
struct Edge {
  i64 w;
  int to, next;
  Edge(i64 _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, i64 w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define for_graph_(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
XorBasis<> xb;
bool vis[N];
std::bitset<64> pre_v[N];
void dfs(int now, std::bitset<64> &v) {
  pre_v[now] = v;
  vis[now] = 1;
  for_graph_(head, e, i, now) {
    v ^= e[i].w;
    if (!vis[to]) dfs(to, v);
    else xb.insert(v ^ pre_v[to]);
    v ^= e[i].w;
  }
}
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define rfor_(i, r, l, vars...)                                           \
  for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; \
       i >= i##end;                                                       \
       --i)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  for_(i, 1ll, m, s, t, d) {
    cin >> s >> t >> d;
    addEdge(s, t, d);
    addEdge(t, s, d);
  }
  std::bitset<64> v;
  dfs(1, v);
  v = pre_v[n];
  rfor_(i, xb.size() - 1, 0)
    if (!v[i]) v ^= xb[i];
  cout << v.to_ullong();
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
