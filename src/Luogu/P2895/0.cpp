#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
namespace BFS {
typedef int _state_t;
typedef int _point_t;
typedef long long _step_t;
const int N = 405, M = 5e4 + 5;
const _state_t __valid__ = -1, __passed__ = -2;
int n;
_state_t __state[N][N];
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
  Point operator+(const Point &other) const {
    Point tmp = *this;
    return tmp += other;
  }
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  _state_t get_state() const { return __state[x][y]; }
  bool valid() const { return x >= 0 && y >= 0 && x < N && y < N; }
  void set_state(_state_t state) const { __state[x][y] = state; }
};
struct Node {
  Point p;
  _step_t time;
  Node operator+=(const Node &other) {
    p += other.p;
    time += other.time;
    return *this;
  }
  Node operator+(const Node &other) const {
    Node tmp = *this;
    return tmp += other;
  }
  bool valid() const {
    return p.valid() &&
           (this->get_state() > time || this->get_state() == __valid__);
  }
  void set_state(_state_t state) const { p.set_state(state); }
  _state_t get_state() const { return p.get_state(); }
  void print() const { cout << p.x << " " << p.y << " " << time << endl; }
};
struct Obstract {
  Point p;
  _step_t time;
  void init() {
    scanf("%d %d %lld", &p.x, &p.y, &time);
    const Point move[5] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (auto i : move) {
      Point now = this->p + i;
      if (now.valid()) {
        if (now.get_state() == __valid__ || time < now.get_state())
          now.set_state(time);
      }
    }
  }
} ob[M];
const Node move[] = {{{1, 0}, 1}, {{0, 1}, 1}, {{-1, 0}, 1}, {{0, -1}, 1}};
std::queue<Node> queue;
void init() {
  memset(__state, 0xff, sizeof(__state));
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) ob[i].init();
}
void bfs() {
  init();
  if ((Point){0, 0}.get_state() == 0) {
    printf("-1");
    return;
  } else if ((Point){0, 0}.get_state() == __valid__) {
    printf("0");
    return;
  }
  queue.push((Node){(Point){0, 0}, 0});
  (Point){0, 0}.set_state(__passed__);
  while (!queue.empty()) {
    Node now = queue.front();
    queue.pop();
    for (auto i : move) {
      Node next = now + i;
      if (next.valid()) {
        if (next.p.get_state() == __valid__) {
          printf("%lld", next.time);
          return;
        }
        next.set_state(__passed__);
        queue.push(next);
      }
    }
  }
  printf("-1");
}
}  // namespace BFS
using BFS::bfs;
int main() {
  bfs();
  return 0;
}
