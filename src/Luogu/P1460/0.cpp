#include <bits/stdc++.h>
using namespace std;
int v, g, minn = 0x3f3f3f3f, len;
int vt[105], fd[105][105], sv[105], ans[105];
bool vis[105];
bool check(int len) {
  static int __[105];
  memset(__, 0, sizeof(__));
  for (int i = 1; i <= len; i++)
    for (int l = 1; l <= v; l++) __[l] += fd[sv[i]][l];
  for (int i = 1; i <= v; i++)
    if (__[i] < vt[i]) return false;
  return true;
}
void dfs() {
  if (len > g || len > minn) return;
  if (check(len) == true) {
    if (minn > len) {
      minn = len;
      for (int i = 1; i <= minn; i++) ans[i] = sv[i];
    }
    return;
  }
  int start = sv[len];
  if (start == 0) start = 0;
  for (int i = start; i <= g; i++) {
    if (vis[i] == false) {
      vis[i] = true;
      sv[++len] = i;
      dfs();
      vis[i] = false;
      sv[len--] = 0;
    }
  }
}
int main() {
  scanf("%d", &v);
  for (int i = 1; i <= v; i++) scanf("%d", &vt[i]);
  scanf("%d", &g);
  for (int i = 1; i <= g; i++)
    for (int l = 1; l <= v; l++) scanf("%d", &fd[i][l]);
  dfs();
  printf("%d ", minn);
  for (int i = 1; i <= minn; i++) printf("%d ", ans[i]);
  return 0;
}
