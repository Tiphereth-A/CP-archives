#include <algorithm>
#include <cstdio>
const int N = 105;
struct Wall {
  int x1, x2, y;
  bool removed;
  bool is_blocked(int s) { return !removed && s <= x2 && s >= x1; }
  bool operator<(const Wall &oth) const {
    return x2 == oth.x2 ? x1 >= oth.x1 : x2 > oth.x2;
  }
} walls[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d%d%*d", &walls[i].x1, &walls[i].y, &walls[i].x2);
      if (walls[i].x1 > walls[i].x2)
        walls[i].x1 ^= walls[i].x2 ^= walls[i].x1 ^= walls[i].x2;
      walls[i].removed = 0;
    }
    std::sort(walls + 1, walls + n + 1);
    int ans = 0;
    for (int spector = 0, cnt; spector <= 100; ++spector) {
      cnt = 0;
      for (int i = 1; i <= n; ++i) cnt += walls[i].is_blocked(spector);
      if (cnt <= k) continue;
      ans += cnt - k;
      for (int i = 1; i <= n; ++i)
        if (walls[i].is_blocked(spector)) {
          --cnt;
          walls[i].removed = 1;
          if (cnt <= k) break;
        }
    }
    printf("%d\n", ans);
  }
  return 0;
}
