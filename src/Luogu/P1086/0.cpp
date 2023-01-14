#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
struct node {
  int x, y, num;
  bool operator<(const node &a) const { return num > a.num; }
} data[500];
int m, n, k, r;
int ans, tot = 1;
void dfs(int s) {
  if (s > tot) return;
  int dis = s == 1 ? data[1].x :
                     std::abs(data[s - 1].x - data[s].x) +
                       std::abs(data[s - 1].y - data[s].y);
  int t = r - dis - 1;
  if (t >= data[s].x) {
    ans += data[s].num;
    r -= dis + 1;
    dfs(s + 1);
  }
  return;
}
int main() {
  cin >> m >> n >> k;
  r = k;
  for (int i = 1; i <= m; i++)
    for (int p, j = 1; j <= n; j++) {
      cin >> p;
      if (p) {
        data[tot] = {i, j, p};
        tot++;
      }
    }
  tot--;
  std::sort(data + 1, data + tot + 1);
  dfs(1);
  printf("%d", ans);
}
