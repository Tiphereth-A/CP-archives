#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
using map_T = char[N][N];
using ans_T = int[N][N];
struct Point {
  int x, y;
  Point(int _x = 0, int _y = 0): x(_x), y(_y) {}
  Point(const Point &_p): x(_p.x), y(_p.y) {}
  Point operator+(const Point &rhs) {
    Point ret(*this);
    ret.x += rhs.x;
    ret.y += rhs.y;
    return ret;
  }
  Point operator+=(const Point &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  bool operator==(const Point &rhs) const { return x == rhs.x && y == rhs.y; }
  int &get_ans(ans_T &ans_in) { return ans_in[x][y]; }
  const char &get_map(const map_T &map_in) const { return map_in[x][y]; }
};
const Point dir[] = {Point(-1, 0), Point(1, 0), Point(0, 1), Point(0, -1)};
int h, w;
map_T maps;
ans_T ans;
bool isvalid(const Point &p) {
  return p.x > 0 && p.y > 0 && p.x <= h && p.y <= w && p.get_map(maps) != '#';
}
int main() {
  scanf("%d%d\n", &h, &w);
  for (int i = 1; i <= h; ++i) scanf("%s", maps[i] + 1);
  queue<Point> q;
  Point p_end;
  list<Point> portals[30];
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j) {
      if (maps[i][j] == 'S') {
        q.push(Point(i, j));
        continue;
      }
      if (maps[i][j] == 'G') {
        p_end = Point(i, j);
        continue;
      }
      if (islower(maps[i][j])) {
        portals[maps[i][j] - 'a'].push_back(Point(i, j));
        continue;
      }
    }
  while (!q.empty()) {
    Point now(q.front());
    q.pop();
    for (const Point &i : dir) {
      Point _(now + i);
      if (!isvalid(_)) continue;
      if (_.get_ans(ans)) continue;
      if (_ == p_end) {
        cout << now.get_ans(ans) + 1;
        return 0;
      }
      _.get_ans(ans) = now.get_ans(ans) + 1;
      q.push(_);
    }
    if (islower(now.get_map(maps))) {
      list<Point> &now_portal = portals[now.get_map(maps) - 'a'];
      bool f = 1;
      for (auto i = now_portal.begin(); i != now_portal.end(); f ? ++i : i) {
        if (*i == now) {
          i = now_portal.erase(i);
          f = 0;
          continue;
        }
        f = 1;
        Point _(*i);
        if (!isvalid(_)) continue;
        if (_.get_ans(ans)) continue;
        if (_ == p_end) {
          cout << now.get_ans(ans) + 1;
          return 0;
        }
        i = now_portal.erase(i);
        f = 0;
        _.get_ans(ans) = now.get_ans(ans) + 1;
        q.push(_);
      }
    }
  }
  cout << -1;
}
