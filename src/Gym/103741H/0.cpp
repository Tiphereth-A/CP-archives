#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e6 + OFFSET, M = 2e6 + OFFSET, K = 21;
const uint32_t MOD = 998244353;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
int in_deg[N];
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
  ++in_deg[y];
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int id[N];
int sz[N];
bool dfs(int now, int val) {
  sz[now] = 1;
  assert(!id[now] || id[now] == val);
  if (id[now] && id[now] == val) return false;
  id[now] = val;
  _for_graph(head, e, i, now) {
    if (!dfs(to, val)) return false;
    sz[now] += sz[to];
  }
  return true;
}
template <typename Tp = i64>
constexpr Tp qpow(Tp a, Tp b = MOD - 2, const Tp &mod = MOD) {
  Tp res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
i64 fact[N * 2], inv_fact[N];
auto __STATIC__ = []() {
  static i64 ffact[N];
  ffact[0] = fact[0] = inv_fact[0] = fact[1] = inv_fact[1] = 1;
  _for(i, 2, N * 2 - 1) fact[i] = fact[i - 1] * i % MOD;
  _for(i, 1, N - 1) ffact[i] = ffact[i - 1] * fact[i] % MOD;
  i64 _ = qpow(ffact[N - 1]);
  _rfor(i, N - 1, 2) {
    inv_fact[i] = _ * ffact[i - 1] % MOD;
    _ = _ * fact[i] % MOD;
  }
  return 0.0;
}();
auto m_choose_n = [](int m, int n, i64 mod = MOD) -> i64 {
  return m < n ? 0 : fact[m] * inv_fact[n] % mod * inv_fact[m - n] % mod;
};
i64 dfs2(int now) {
  i64 ans = fact[sz[now] - 1];
  _for_graph(head, e, i, now) {
    ans = ans * inv_fact[sz[to]] % MOD;
    ans = ans * dfs2(to) % MOD;
  }
  return ans;
}
i64 f[N];
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m, x, y) {
    cin >> x >> y;
    addEdge(y, x);
  }
  int cnt_id = 0;
  _for(i, 1, n)
    if (!in_deg[i] && !dfs(i, ++cnt_id)) _run_return_void(cout << '0');
  _for(i, 1, n)
    if (!id[i]) _run_return_void(cout << '0');
  i64 ans = fact[n];
  _for(i, 1, n) {
    if (in_deg[i]) continue;
    ans = ans * dfs2(i) % MOD;
    ans = ans * inv_fact[sz[i]] % MOD;
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
