#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
namespace BFS {
typedef int _state_t;
typedef int _point_t;
typedef long long _step_t;
typedef char _map_t;
const int N = 305, M = 305;
const _state_t __valid__ = 0, __forbidden__ = 1;
int n, m;
_state_t __state[N][M];
_map_t __map[N][M];
_step_t __step[N][M];
struct Point {
  _point_t x, y;
  Point operator=(const Point &other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  Point operator+=(const Point &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  _state_t get_state() const { return __state[x][y]; }
  bool valid() const {
    return x > 0 && y > 0 && x <= n && y <= m &&
           this->get_state() != __forbidden__;
  }
  void set_state(_state_t state) const { __state[x][y] = state; }
};
struct Node {
  Point p;
  _step_t step;
  Node operator+=(const Node &other) {
    p += other.p;
    step += other.step;
    return *this;
  }
  Node operator+(const Node &other) const {
    Node tmp = *this;
    return tmp += other;
  }
  bool valid() const { return p.valid(); }
  void set_state(_state_t state) const { p.set_state(state); }
  _state_t get_state() const { return p.get_state(); }
};
const Node move[] = {{{1, 0}, 1}, {{0, 1}, 1}, {{-1, 0}, 1}, {{0, -1}, 1}};
std::deque<Node> queue;
Point start, end, trans[256][2];
void init() {
  scanf("%d%d\n", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%s", __map[i] + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      switch (__map[i][j]) {
        case '#':
          __step[i][j] = -1;
          __state[i][j] = __forbidden__;
          break;
        case '@': start = (Point){i, j}; break;
        case '=': end = (Point){i, j}; break;
        default:
          if (isalpha(__map[i][j])) {
            __state[i][j] = -__map[i][j];
            if (trans[__map[i][j]][0] == (Point){0, 0})
              trans[__map[i][j]][0] = (Point){i, j};
            else trans[__map[i][j]][1] = (Point){i, j};
          }
          break;
      }
    }
  for (int i = 0; i < 256; ++i) {
    Point &now_0 = trans[i][0], &now_1 = trans[i][1];
    if ((now_0 == (Point){0, 0}) ^ (now_1 == (Point){0, 0})) {
      now_0.set_state(__valid__);
      now_1.set_state(__valid__);
      now_0 = now_1 = {0, 0};
    }
  }
}
void bfs() {
  init();
  queue.push_back((Node){start, 0});
  while (!queue.empty()) {
    Node now = queue.front();
    queue.pop_front();
    if (now.get_state() < 0) {
      if (now.p == trans[-now.get_state()][0])
        now.p = trans[-now.get_state()][1];
      else now.p = trans[-now.get_state()][0];
    }
    for (auto i : move) {
      Node next = now + i;
      if (next.valid()) {
        if (!next.get_state()) next.set_state(__forbidden__);
        if (next.p == end) {
          printf("%lld", next.step);
          return;
        }
        __step[next.p.x][next.p.y] = next.step;
        queue.push_back(next);
      }
    }
  }
}
}  // namespace BFS
using BFS::bfs;
int main() {
  bfs();
  return 0;
}
