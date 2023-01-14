#include <bits/stdc++.h>
using namespace std;
const char m[] = " harbin";
int cnt[7][7];
bool vis[7];
bool dfs(int dep = 1) {
  if (dep > 6) {
    for (int i = 1; i <= 6; ++i)
      if (!vis[i]) return 0;
    return 1;
  }
  for (int i = 1; i <= 6; ++i)
    if (!vis[i] && cnt[dep][i]) {
      vis[i] = 1;
      if (dfs(dep + 1)) return 1;
      vis[i] = 0;
    }
  return 0;
}
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    string _;
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= 6; ++i) {
      cin >> _;
      for (char &ch : _) {
        for (int j = 1; j <= 6; ++j)
          if (ch == m[j]) ++cnt[i][j];
      }
    }
    cout << (dfs() ? "Yes" : "No") << endl;
  __end_kase:;
  }
  return 0;
}
