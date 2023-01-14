#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const i64 INF = INT64_MAX;
template <class Tp>
struct point_type {
  using data_type = Tp;
  using self = point_type<Tp>;
  Tp x, y;
  static bool less_x(const self &lhs, const self &rhs) { return lhs.x < rhs.x; }
  static bool less_y(const self &lhs, const self &rhs) { return lhs.y < rhs.y; }
  friend constexpr data_type dis_sqr(const self &lhs, const self &rhs) {
    return (rhs.x - lhs.x) * (rhs.x - lhs.x) +
           (rhs.y - lhs.y) * (rhs.y - lhs.y);
  }
};
using data_t = i64;
using vec = vector<point_type<data_t>>;
vec points;
void mcp_dis_sqr(const vec::iterator l, const vec::iterator r, data_t &dis) {
  if (r - l <= 1) return;
  auto mid = l + (r - l) / 2;
  data_t mid_x = mid->x;
  mcp_dis_sqr(l, mid, dis);
  mcp_dis_sqr(mid, r, dis);
  inplace_merge(l, mid, r, point_type<data_t>::less_y);
  vector<point_type<data_t>> _;
  for (auto i = l; i != r; ++i)
    if (abs(i->x - mid_x) <= dis) _.push_back(*i);
  for (auto i = _.begin(), j = i; i != _.end(); ++i) {
    while (j != _.end() && j->y - i->y <= dis) ++j;
    for (auto k = i + 1; k != j; ++k) dis = min(dis, dis_sqr(*i, *k));
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  _for(i, 1, n, x, y) {
    cin >> x >> y;
    points.push_back({x, y});
  }
  sort(points.begin(), points.end(), point_type<data_t>::less_x);
  data_t ans = INF;
  mcp_dis_sqr(points.begin(), points.end(), ans);
  cout << fixed << setprecision(4) << sqrt(ans);
  return 0;
}
