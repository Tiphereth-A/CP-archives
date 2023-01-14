#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
struct node {
  int x, y;
  bool operator<(const node &rhs) const {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
} a[10005];
int main() {
  int n;
  while (scanf("%d", &n) && n) {
    for (int i = 0; i < n; ++i) scanf("%d%d", &a[i].x, &a[i].y);
    int ans = 1;
    sort(a, a + n);
    for (int i = 1, min = a[0].y; i < n; ++i)
      if (min > a[i].y) {
        min = a[i].y;
        ++ans;
      }
    printf("%d\n", ans);
  }
  return 0;
}
