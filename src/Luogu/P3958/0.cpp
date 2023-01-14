#include <bits/stdc++.h>
typedef long long ll;
#define M 100005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
int pre[1005], up[M], down[M];
struct point {
  ll x, y, z;
} p[M];
int find(int x) {
  int a = x, b = x, c;
  while (a != pre[a]) a = pre[a];
  while (b != pre[b]) {
    c = pre[b];
    pre[b] = a;
    b = c;
  }
  return a;
}
double dist(point p1, point p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) +
              (p1.z - p2.z) * (p1.z - p2.z));
}
int main() {
  int t, n, h;
  scanf("%d", &t);
  ll r;
  while (t--) {
    scanf("%d%d%ld", &n, &h, &r);
    int tot1 = 0, tot2 = 0;
    _for(i, 1, n) pre[i] = i;
    _for(i, 1, n) {
      scanf("%ld%ld%ld", &p[i].x, &p[i].y, &p[i].z);
      if (p[i].z + r >= h) {
        tot1++;
        up[tot1] = i;
      }
      if (p[i].z <= r) {
        tot2++;
        down[tot2] = i;
      }
      _for(j, 1, i) {
        if (dist(p[j], p[i]) <= 2 * r) {
          int fx = find(i), fy = find(j);
          if (fx != fy) pre[fx] = fy;
        }
      }
    }
    int f = 0;
    _for(i, 1, tot1) {
      _for(j, 1, tot2) {
        if (find(up[i]) == find(down[j])) {
          f = 1;
          break;
        }
      }
      if (f) break;
    }
    if (f) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
