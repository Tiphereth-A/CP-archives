#include <bits/stdc++.h>
#define _T_ANT(i) for (int i = 1; i <= ant_alive; ++i)
#define _T_TURRET(i) for (int i = 1; i <= s; ++i)
const int MAX_TURRET = 25, MAX_ANT = 11;
const int MAX_N = 9, MAX_M = 9;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int has_taken[MAX_N][MAX_M];
int msg[MAX_N][MAX_M];
bool cake_disappeared;
bool game_over;
int ant_alive = 0, ant_total = 0;
int target_all;
int n, m, s, d, r, t;
i64 r_sqr;
namespace GEO {
i64 get_dis_sqr(int x1, int y1, int x2, int y2) {
  return 1ll * (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
void get_dis_to_segment_sqr(
  i64 A, i64 B, i64 C, int x, int y, i64 &absFSqr, i64 &lineSqr) {
  absFSqr = (A * x + B * y + C) * (A * x + B * y + C);
  lineSqr = A * A + B * B;
}
i64 cross(i64 x1, i64 y1, i64 x2, i64 y2) { return x1 * x2 + y1 * y2; }
}  // namespace GEO
using namespace GEO;
void dec_msg() {
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j) {
      if (msg[i][j]) --msg[i][j];
    }
}
bool check_block_valid(int x, int y) {
  return !(x < 0 || x > n || y < 0 || y > m || has_taken[x][y]);
}
struct ANT {
  int x_now, y_now;
  int x_pre, y_pre;
  int blood_now, blood_max;
  bool taking_cake;
  int age;
  int level;
  ANT(int X_now = 0,
      int Y_now = 0,
      int X_pre = 0,
      int Y_pre = 0,
      int Blood = 0,
      bool Taking_cake = false,
      int Age = 0,
      int Level = 0) {
    x_now = X_now;
    y_now = Y_now;
    x_pre = X_pre;
    y_pre = Y_pre;
    blood_now = blood_max = Blood;
    taking_cake = Taking_cake;
    age = Age;
    level = Level;
  }
  void add_age() { ++age; }
  void leave_msg() { msg[x_now][y_now] += taking_cake ? 5 : 2; }
  void move() {
    int msg_max = -1;
    int x_final = 0, y_final = 0;
    int dir_final = 0;
    for (int i = 0; i <= 3; ++i) {
      int x_tmp = x_now + dx[i], y_tmp = y_now + dy[i];
      if (!check_block_valid(x_tmp, y_tmp)) continue;
      if (msg_max < msg[x_tmp][y_tmp] && (x_tmp != x_pre || y_tmp != y_pre)) {
        msg_max = msg[x_tmp][y_tmp];
        x_final = x_tmp;
        y_final = y_tmp;
        dir_final = i;
      }
    }
    if (age % 5 == 4 && msg_max != -1) {
      msg_max = -1;
      for (int i = 1; i <= 4; ++i) {
        int dir_tmp = (dir_final - i) % 4;
        if (dir_tmp < 0) dir_tmp += 4;
        int x_tmp = x_now + dx[dir_tmp], y_tmp = y_now + dy[dir_tmp];
        if (!check_block_valid(x_tmp, y_tmp)) continue;
        if (msg_max < msg[x_tmp][y_tmp] && (x_tmp != x_pre || y_tmp != y_pre)) {
          msg_max = msg[x_tmp][y_tmp];
          x_final = x_tmp;
          y_final = y_tmp;
          dir_final = dir_tmp;
          break;
        }
      }
    }
    x_pre = x_now;
    y_pre = y_now;
    if (msg_max < 0) return;
    has_taken[x_now][y_now] = 0;
    has_taken[x_final][y_final] = age + 1;
    x_now = x_final;
    y_now = y_final;
  }
  void get_cake() {
    if (cake_disappeared) return;
    if (x_now == n && y_now == m) {
      taking_cake = cake_disappeared = true;
      blood_now += (int)(blood_max / 2);
      if (blood_now > blood_max) blood_now = blood_max;
    }
  }
  void print() {
    printf("%d %d %d %d %d\n", age, level, blood_now, x_now, y_now);
  }
} ant[MAX_ANT];
struct TURRET {
  int x, y;
  TURRET(int X = 0, int Y = 0): x(X), y(Y) {}
  void attack() {
    if (!cake_disappeared ||
        get_dis_sqr(x, y, ant[target_all].x_now, ant[target_all].y_now) >
          r_sqr) {
      int target_antID;
      i64 dis_sqr, dis_sqr_min = 0x3f3f3f3f3f3f3f3f;
      _T_ANT(i) {
        dis_sqr = get_dis_sqr(x, y, ant[i].x_now, ant[i].y_now);
        if (dis_sqr <= r_sqr) {
          if (dis_sqr < dis_sqr_min) {
            dis_sqr_min = dis_sqr;
            target_antID = i;
          }
        }
      }
      if (dis_sqr_min > r_sqr) return;
      ant[target_antID].blood_now -= d;
      return;
    } else {
      i64 A = 1ll * y - ant[target_all].y_now,
          B = 1ll * ant[target_all].x_now - x;
      i64 C = -1ll * (x * A + y * B);
      i64 x1 = ant[target_all].x_now - x, y1 = ant[target_all].y_now - y;
      i64 dis_tmp =
        get_dis_sqr(x, y, ant[target_all].x_now, ant[target_all].y_now);
      _T_ANT(i) {
        if (ant[i].taking_cake) {
          ant[i].blood_now -= d;
          continue;
        }
        if (get_dis_sqr(x, y, ant[i].x_now, ant[i].y_now) > dis_tmp) continue;
        i64 x2 = ant[i].x_now - x, y2 = ant[i].y_now - y;
        if (cross(x1, y1, x2, y2) <= 0) continue;
        i64 tmp1, tmp2;
        get_dis_to_segment_sqr(A, B, C, ant[i].x_now, ant[i].y_now, tmp1, tmp2);
        if (tmp1 * 4 <= tmp2) { ant[i].blood_now -= d; }
      }
    }
  }
} turret[MAX_TURRET];
bool check_game_over() {
  if (!cake_disappeared) return false;
  _T_ANT(i) {
    if (ant[i].x_now == 0 && ant[i].y_now == 0 && ant[i].taking_cake) {
      return game_over = true;
    }
  }
  return false;
}
void ant_appear() {
  if (ant_alive == 6 || has_taken[0][0]) return;
  has_taken[0][0] = 1;
  ++ant_alive;
  ++ant_total;
  int level_now = 1 + (ant_total - 1) / 6;
  int blood_max_now = (int)(4.0 * pow(1.1, level_now));
  ant[ant_alive] = ANT(0, 0, -1, -1, blood_max_now, false, 0, level_now);
}
void ant_clear(int antID) {
  for (int i = antID + 1; i <= ant_alive; ++i) { ant[i - 1] = ant[i]; }
  --ant_alive;
}
void clear() {
  _T_ANT(i) {
    if (ant[i].blood_now < 0) {
      if (ant[i].taking_cake) {
        cake_disappeared = false;
        target_all = 0;
      }
      has_taken[ant[i].x_now][ant[i].y_now] = 0;
      ant_clear(i);
      --i;
    }
  }
}
void debug() {
  printf("%d\n", ant_alive);
  _T_ANT(i) {
    printf("#%d ", i);
    if (ant[i].taking_cake) printf("#");
    ant[i].print();
  }
  puts("信息素：");
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) printf("%d ", msg[i][j]);
    puts("");
  }
  puts("被占用的格子：");
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) printf("%d ", has_taken[i][j]);
    puts("");
  }
  puts("");
}
int main() {
  scanf("%d%d%d%d%d", &n, &m, &s, &d, &r);
  r_sqr = 1ll * r * r;
  _T_TURRET(i) {
    int x_tmp, y_tmp;
    scanf("%d%d", &x_tmp, &y_tmp);
    has_taken[x_tmp][y_tmp] = 500;
    turret[i] = TURRET(x_tmp, y_tmp);
  }
  scanf("%d", &t);
  for (int time_passed = 1; time_passed <= t; ++time_passed) {
    ant_appear();
    _T_ANT(i) {
      ant[i].leave_msg();
      ant[i].move();
    }
    _T_ANT(i) {
      ant[i].get_cake();
      if (ant[i].taking_cake) target_all = i;
    }
    if (!cake_disappeared) target_all = 0;
    _T_TURRET(i) { turret[i].attack(); }
    clear();
    if (check_game_over()) {
      printf("Game over after %d seconds", time_passed);
      break;
    }
    _T_ANT(i) { ant[i].add_age(); }
    dec_msg();
  }
  puts(game_over ? "" : "The game is going on");
  printf("%d\n", ant_alive);
  _T_ANT(i) { ant[i].print(); }
  return 0;
}
