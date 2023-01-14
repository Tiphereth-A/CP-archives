#include <bits/stdc++.h>
using namespace std;
typedef struct {
  int x;
  int y;
  int num;
} node;
int m, n, k, r, p;
node point[500];
int ans;
int tot = 1;
bool cmp(node a, node b) { return a.num > b.num; }
void dfs(int s) {
  int t, dist;
  if (s > tot) return;
  if (s == 1) dist = point[1].x;
  else
    dist = abs(point[s - 1].x - point[s].x) + abs(point[s - 1].y - point[s].y);
  t = r - dist - 1;
  if (t >= point[s].x) {
    ans += point[s].num;
    r = r - dist - 1;
    dfs(s + 1);
  }
  return;
}
int main() {
  scanf("%d%d%d", &m, &n, &k);
  r = k;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++) {
      scanf("%d", &p);
      if (p) {
        point[tot].x = i;
        point[tot].y = j;
        point[tot].num = p;
        tot++;
      }
    }
  tot--;
  sort(point + 1, point + tot + 1, cmp);
  dfs(1);
  printf("%d", ans);
}
