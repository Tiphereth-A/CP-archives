#include <bits/stdc++.h>
using namespace std;
int n;
string ss[30];
int __[30][30];
int vis[30];
int ff(int x, int y) {
  bool pp = true;
  int ky = 0;
  for (int k = ss[x].size() - 1; k >= 0; k--) {
    for (int kx = k; kx < ss[x].size(); kx++) {
      if (ss[x][kx] != ss[y][ky++]) {
        pp = false;
        break;
      }
    }
    if (pp == true) return ss[x].size() - k;
    ky = 0;
    pp = true;
  }
  return 0;
}
char ch;
int ans = -1, ans_ = 0;
void dfs(int p) {
  bool jx = false;
  for (int j = 1; j <= n; j++) {
    if (vis[j] >= 2) continue;
    if (__[p][j] == 0) continue;
    if (__[p][j] == ss[p].size() || __[p][j] == ss[j].size()) continue;
    ans_ += ss[j].size() - __[p][j];
    vis[j]++;
    jx = true;
    dfs(j);
    ans_ -= ss[j].size() - __[p][j];
    vis[j]--;
  }
  if (jx == false) ans = max(ans, ans_);
  return;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) cin >> ss[i];
  cin >> ch;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) __[i][j] = ff(i, j);
  for (int i = 1; i <= n; i++)
    if (ss[i][0] == ch) {
      vis[i]++;
      ans_ = ss[i].size();
      dfs(i);
      vis[i] = 0;
    }
  printf("%d", ans);
  return 0;
}
