#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
bool merge(int x, int y) {
  int fx = find(x), fy = find(y);
  return fx == fy ? false : (fa[fx] = fy, true);
}
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[N * 2];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define for_graph_(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int sss, ff;
bool dfs(int now, int fa = 0) {
  if (now == sss && fa) {
    ff = fa;
    return true;
  }
  for_graph_(head, e, i, now) {
    if (to == fa) continue;
    if (dfs(to, now)) return true;
  }
  return false;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  cnt_edge = 0;
  memset(head, 0, sizeof(head[0]) * (n + 2));
  for_(i, 1, n) fa[i] = i;
  vector<pair<int, int>> eds;
  eds.reserve(m);
  string s(m, '0');
  for_(i, 0, m - 1, x, y) {
    cin >> x >> y;
    eds.emplace_back(x, y);
    if (!merge(x, y)) s[i] = '1';
    else {
      addEdge(x, y, i);
      addEdge(y, x, i);
    }
  }
  if (m < n + 2) {
    cout << s << '\n';
    return;
  }
  set<int> ss;
  for_(i, 0, m - 1)
    if (s[i] & 1) {
      if (ss.count(eds[i].first) && ss.count(eds[i].second)) {
        s[i] = '0';
        addEdge(eds[i].first, eds[i].second, i);
        addEdge(eds[i].second, eds[i].first, i);
        dfs(sss = eds[i].first);
        if (ff == eds[i].second) dfs(sss = eds[i].second);
        int f = 0;
        for_graph_(head, e, j, eds[i].first) {
          if (to == ff) {
            f = e[j].w;
            break;
          }
        }
        if (!f)
          for_graph_(head, e, j, eds[i].second) {
            if (to == ff) {
              f = e[j].w;
              break;
            }
          }
        s[f] = '1';
        break;
      } else {
        ss.insert(eds[i].first);
        ss.insert(eds[i].second);
      }
    }
  cout << s << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
