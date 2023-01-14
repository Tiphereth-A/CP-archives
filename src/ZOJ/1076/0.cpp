#include <algorithm>
#include <cstdio>
struct Node {
  int s, e, id;
  bool operator<(const Node &oth) const {
    return e == oth.e ? s > oth.s : e < oth.e;
  }
} a[1005];
int main() {
  int n;
  while (scanf("%d", &n) && n) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", &a[i].s, &a[i].e);
      a[i].id = i;
    }
    std::sort(a + 1, a + n + 1);
    printf("%d", a[1].id);
    for (int i = 2, now = a[1].e; i <= n; ++i)
      if (a[i].s >= now) {
        printf(" %d", a[i].id);
        now = a[i].e;
      }
    puts("");
  }
}
