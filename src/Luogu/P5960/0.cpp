#include <bits/stdc++.h>
using namespace std;
using u32 = std::uint32_t;
#define OPERATOR_OVERRIED_PAIR_(oper)                                       \
  template <typename Tp, typename Up>                                       \
  constexpr std::pair<Tp, Up> &operator oper##=(                            \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                 \
    lhs.first oper## = rhs.first;                                           \
    lhs.second oper## = rhs.second;                                         \
    return lhs;                                                             \
  }                                                                         \
  template <typename Tp, typename Up>                                       \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,          \
                                            const std::pair<Tp, Up> &rhs) { \
    return lhs oper## = rhs;                                                \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <typename Tp, typename Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_return_void_(expressions) run_exec_(expressions, return)
template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <typename Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <typename Tp>
auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  if (&os == &std::cerr) return os << "(" << p.first << ", " << p.second << ")";
  return os << p.first << " " << p.second;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  if (&os == &std::cerr) os << "[";
  if (&os == &std::cerr)
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
  else
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
const u32 M = 2e5 + OFFSET;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int dis[N], dep[N];
bool vis[N];
bool bellman_ford(int n, int s) {
  memset(dis, 0x3f, sizeof(dis[0]) * (n + 1));
  dis[s] = 0;
  vis[s] = true;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    vis[now] = false;
    _for_graph(head, e, i, now)
      if (dis[to] > dis[now] + e[i].w) {
        dis[to] = dis[now] + e[i].w;
        if (vis[to]) continue;
        if (++dep[to] > n) return false;
        vis[to] = true;
        q.push(to);
      }
  }
  return true;
}
auto solve([[maybe_unused]] int t_) -> void {
  int n, m;
  cin >> n >> m;
  for_(i, 1, n) addEdge(0, i, 0);
  for_(i, 1, m, c1, c2, y) {
    cin >> c1 >> c2 >> y;
    addEdge(c2, c1, y);
  }
  if (!bellman_ford(n, 0)) run_return_void_(cout << "NO");
  for_(i, 1, n) cout << dis[i] << " \n"[i == n];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
