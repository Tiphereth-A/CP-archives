#include <bits/stdc++.h>
using namespace std;
int n;
struct node {
  int x, y;
} a[30];
int b[30];
int ans;
bool cmp(node aa, node bb) {
  if (aa.y == bb.y) return aa.x < bb.x;
  return aa.y < bb.y;
}
int f(int num, int d, int begin, int p1) {
  if (num != 1 && d == begin && p1 == 1) return 1;
  if (p1 == 0) {
    if (a[d].y == a[d + 1].y) return f(num + 1, d + 1, begin, 1);
    else return 0;
  }
  if (p1 == 1) return f(num + 1, b[d], begin, 0);
}
bool check() {
  for (int j = 1; j <= n; j++)
    if (f(1, j, j, 1) == 1) return 1;
  return 0;
}
void dfs(int x) {
  if (x == n + 1) {
    if (check() == 1) ans++;
    return;
  }
  if (b[x] == 0) {
    for (int i = x + 1; i <= n; i++)
      if (b[i] == 0) {
        b[i] = x;
        b[x] = i;
        dfs(x + 1);
        b[i] = b[x] = 0;
      }
  }
  if (b[x] != 0) dfs(x + 1);
  return;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
  sort(a + 1, a + n + 1, cmp);
  dfs(1);
  printf("%d\n", ans);
  return 0;
}
