#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
const int N = 1e5 + 5;
const int M = 2e5 + 5;
struct Edge {
  double w;
  int to, next;
  Edge(double _w = 0, int _to = 0, int _next = 0)
    : w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, double w = 0) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
  e[++cnt_edge] = Edge(w, x, head[y]);
  head[y] = cnt_edge;
}
double dis[N];
void dijkstra(int s) {
  priority_queue<pair<double, int>,
                 vector<pair<double, int>>,
                 greater<pair<double, int>>>
    q;
  fill(dis, dis + N, DBL_MAX / 4);
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (dis[now] < dis_now) continue;
    for (int i = head[now], to; i; i = e[i].next)
      if (dis[to = e[i].to] > dis[now] + e[i].w)
        q.emplace(dis[to] = dis[now] + e[i].w, to);
  }
}
constexpr int dot(pair<int, int> const &o,
                  pair<int, int> const &p1,
                  pair<int, int> const &p2) {
  return (p1.first - o.first) * (p2.first - o.first) +
         (p1.second - o.second) * (p2.second - o.second);
}
constexpr int dist2(pair<int, int> const &p1, pair<int, int> const &p2) {
  return dot(p1, p2, p2);
}
constexpr double dist(pair<int, int> const &p1, pair<int, int> const &p2) {
  return sqrt(dist2(p1, p2));
}
struct City {
  pair<int, int> p1, p2, p3, p4;
  int t;
  City(int x1, int y1, int x2, int y2, int x3, int y3, int t)
    : p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(0, 0), t(t) {
    if (dot(p2, p1, p3) == 0) swap(p1, p2);
    if (dot(p3, p1, p2) == 0) swap(p1, p3);
    p4 = {p2.first + p3.first - p1.first, p2.second + p3.second - p1.second};
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int s, t, a, b;
  cin >> s >> t >> a >> b;
  cnt_edge = 0;
  memset(head, 0, sizeof(head));
  int sp = 1, ep = 2;
  auto encode = [](int x, int y) { return x * 4 + y + 2; };
  addEdge(sp, encode(a - 1, 1));
  addEdge(sp, encode(a - 1, 2));
  addEdge(sp, encode(a - 1, 3));
  addEdge(sp, encode(a - 1, 4));
  addEdge(ep, encode(b - 1, 1));
  addEdge(ep, encode(b - 1, 2));
  addEdge(ep, encode(b - 1, 3));
  addEdge(ep, encode(b - 1, 4));
  vector<City> v;
  v.reserve(s);
  for_(i, 1, s, x1, y1, x2, y2, x3, y3, tt) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> tt;
    v.emplace_back(x1, y1, x2, y2, x3, y3, tt);
  }
#define EII(idx1, idx2)    \
  addEdge(encode(i, idx1), \
          encode(i, idx2), \
          dist(v[i].p##idx1, v[i].p##idx2) * v[i].t)
#define EIJ(idx1, idx2) \
  addEdge(              \
    encode(i, idx1), encode(j, idx2), dist(v[i].p##idx1, v[j].p##idx2) * t)
#define EI(idx1) \
  EIJ(idx1, 1);  \
  EIJ(idx1, 2);  \
  EIJ(idx1, 3);  \
  EIJ(idx1, 4)
  for_(i, 0, s - 1) {
    EII(1, 2);
    EII(1, 3);
    EII(1, 4);
    EII(2, 3);
    EII(2, 4);
    EII(3, 4);
    for_(j, i + 1, s - 1) {
      EI(1);
      EI(2);
      EI(3);
      EI(4);
    }
  }
  dijkstra(sp);
  cout << dis[ep] << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cout << fixed << setprecision(1);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
