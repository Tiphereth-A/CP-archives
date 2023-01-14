#include <cstdio>
#include <utility>
using namespace std;
typedef double ldb;
typedef pair<ldb, ldb> point;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define x first
#define y second
point operator+(const point &lhs, const point &rhs) {
  return make_pair(lhs.x + rhs.x, lhs.y + rhs.y);
}
point operator*(const point &lhs, ldb rhs) {
  return make_pair(lhs.x * rhs, lhs.y * rhs);
}
ldb get_area(const point &p0, const point &p1, const point &p2) {
  return (p0.x * p1.y + p1.x * p2.y + p2.x * p0.y - p0.x * p2.y - p0.y * p1.x -
          p1.y * p2.x) /
         2;
}
int main() {
  int kase;
  scanf("%d", &kase);
  int n;
  point p0, p1, p2;
  int x, y;
  while (kase--) {
    scanf("%d", &n);
    scanf("%d%d", &x, &y);
    p0 = make_pair(x, y);
    scanf("%d%d", &x, &y);
    p1 = make_pair(x, y);
    point ans = make_pair(0, 0);
    ldb area = 0;
    _for(i, 3, n) {
      scanf("%d%d", &x, &y);
      p2 = make_pair(x, y);
      ldb now_area = get_area(p0, p1, p2);
      ans = ans + (p0 + p1 + p2) * now_area;
      area += now_area;
      p1 = p2;
    }
    printf("%.2lf %.2lf\n", ans.x / area / 3, ans.y / area / 3);
  }
  return 0;
}
