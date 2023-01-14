#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int s, p, xt, yt, l, r, mid, sum;
struct Point {
  int x, y;
} P[N];
struct DSU {
  int f[N];
  void clear(int x) {
    for (int i = 1; i <= x; i++) f[i] = i;
  }
  int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
  }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    f[y] = x;
  }
  bool same(int x, int y) { return (find(x) == find(y)); }
} BCJ;
int dis(Point a, Point b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int main() {
  scanf("%d%d", &s, &p);
  for (int i = 1; i <= p; i++) {
    scanf("%d%d", &xt, &yt);
    P[i] = (Point){xt, yt};
  }
  for (int i = 1; i <= p; i++)
    for (int j = i + 1; j <= p; j++) r = max(dis(P[i], P[j]), r);
  while (l < r) {
    mid = (l + r) >> 1;
    BCJ.clear(p);
    sum = p;
    for (int i = 1; i <= p; i++) {
      for (int j = i + 1; j <= p; j++) {
        if (!BCJ.same(i, j) && dis(P[i], P[j]) <= mid) {
          BCJ.merge(i, j);
          sum--;
        }
      }
    }
    if (sum <= s) r = mid;
    else l = mid + 1;
  }
  printf("%.2lf\n", sqrt(l));
  return 0;
}
